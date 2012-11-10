// Copyright (c) 2012  David Muse
// See the file COPYING for more information

#include <sqlrloggers/neowiz.h>
#include <sqlrconnection.h>
#include <rudiments/charstring.h>
#include <rudiments/directory.h>
#include <rudiments/file.h>
#include <rudiments/permissions.h>
#include <rudiments/filesystem.h>
#include <rudiments/datetime.h>
#include <debugprint.h>

#ifdef RUDIMENTS_NAMESPACE
using namespace rudiments;
#endif

extern "C" {
	sqlrlogger	*new_neowiz(xmldomnode *parameters) {
		return new neowiz(parameters);
	}
}

neowiz::neowiz(xmldomnode *parameters) : sqlrlogger(parameters) {
	querylogname=NULL;
}

neowiz::~neowiz() {
printf("neowiz flushing write buffer\n");
	querylog.flushWriteBuffer(-1,-1);
}

bool neowiz::init(sqlrconnection_svr *sqlrcon) {
	debugFunction();
printf("neowiz...\n");

	cmdline	*cmdl=sqlrcon->cmdl;

	// build up the query log name
	size_t	querylognamelen;
	delete[] querylogname;
	if (charstring::length(cmdl->getLocalStateDir())) {

		// create the directory
		querylognamelen=charstring::length(cmdl->getLocalStateDir())+14+
				charstring::length(cmdl->getId())+1+1;
		querylogname=new char[querylognamelen];
		snprintf(querylogname,querylognamelen,
				"%s/sqlrelay/log/%s",
				cmdl->getLocalStateDir(),cmdl->getId());
		directory::create(querylogname,
				permissions::evalPermString("rwxrwxrwx"));

		// create the log file name
		querylognamelen=charstring::length(cmdl->getLocalStateDir())+14+
				charstring::length(cmdl->getId())+10+1;
		delete[] querylogname;
		querylogname=new char[querylognamelen];
		snprintf(querylogname,querylognamelen,
				"%s/sqlrelay/log/%s/query.log",
				cmdl->getLocalStateDir(),cmdl->getId());
	} else {

		// create the directory
		querylognamelen=charstring::length(LOG_DIR)+1+
				charstring::length(cmdl->getId())+1+1;
		querylogname=new char[querylognamelen];
		snprintf(querylogname,querylognamelen,
				"%s/%s",LOG_DIR,cmdl->getId());
		directory::create(querylogname,
				permissions::evalPermString("rwxrwxrwx"));
printf("dir: %s\n",querylogname);

		// create the log file name
		querylognamelen=charstring::length(LOG_DIR)+1+
				charstring::length(cmdl->getId())+10+1;
		delete[] querylogname;
		querylogname=new char[querylognamelen];
		snprintf(querylogname,querylognamelen,
				"%s/%s/query.log",LOG_DIR,cmdl->getId());
printf("file: %s\n",querylogname);
	}

	// remove any old log file
	file::remove(querylogname);

	// create the new log file
	if (!querylog.create(querylogname,
				permissions::evalPermString("rw-------"))) {
		return false;
	}

	// optimize
	filesystem	fs;
	fs.initialize(querylogname);
	querylog.setWriteBufferSize(fs.getOptimumTransferBlockSize());
	return true;
}

bool neowiz::run(sqlrconnection_svr *sqlrcon, sqlrcursor_svr *sqlrcur) {
	debugFunction();

	// reinit the log if the file was switched
	ino_t	inode1=querylog.getInode();
	ino_t	inode2;
	if (!file::getInode(querylogname,&inode2) || inode1!=inode2) {
		querylog.flushWriteBuffer(-1,-1);
		querylog.close();
		init(sqlrcon);
	}

	// get error, if there was one
	static char	errorcodebuf[100+1];
	errorcodebuf[0]='\0';
	if (sqlrcur->queryresult) {
		charstring::copy(errorcodebuf,"0");
	} else {
		snprintf(errorcodebuf,100,sqlrcur->queryerror);
	}

	// escape the query
	static char	sqlbuf[7000+1];
	strescape(sqlrcur->querybuffer,sqlbuf,7000);

	// escape the client info
	static char	infobuf[1024+1];
	strescape(sqlrcon->clientinfo,infobuf,1024);

	// escape the input bind variables
	char	bindbuf[1000+1];
	descInputBinds(sqlrcur,bindbuf,1000);

	// get the client address
	char	*clientaddrbuf=NULL;
	if (sqlrcon->clientsock) {
		clientaddrbuf=sqlrcon->clientsock->getPeerAddress();
		if (!clientaddrbuf) {
			clientaddrbuf=charstring::duplicate("UNIX");
		}
	} else {
		clientaddrbuf=charstring::duplicate("internal");
	}

	// get the execution time
	uint64_t	sec=sqlrcur->commandendsec-sqlrcur->commandstartsec;
	uint64_t	usec=sqlrcur->commandendusec-sqlrcur->commandstartusec;
	
	// get the current date/time
	datetime	dt;
	dt.getSystemDateAndTime();

	// write everything into an output buffer, pipe-delimited
	snprintf(querylogbuf,sizeof(querylogbuf)-1,
		"%04d-%02d-%02d %02d:%02d:%02d|%d|%f|%s|%lld|%s|%s|%f|%s|%s|\n",
		dt.getYear(),
		dt.getMonth(),
		dt.getDayOfMonth(),
		dt.getHour(),
		dt.getMinutes(),
		dt.getSeconds(),
		sqlrcon->handoffindex, 
		sec+usec/1000000.0,
		errorcodebuf,
		(sqlrcur->lastrowvalid)?sqlrcur->lastrow:0,
        	infobuf,
		sqlbuf,
		sec+usec/1000000.0,
		clientaddrbuf,
		bindbuf
		);

	// clean up
	delete[] clientaddrbuf;

	// write that buffer to the log file
	return (querylog.write(querylogbuf)==charstring::length(querylogbuf));
}

int neowiz::strescape(const char *str, char *buf, int limit) {
	// from oracpool my_strescape()
	register char	*q=buf;
	const char	*strend=str+charstring::length(str);
	for (register const char *p=str; p<strend; p++) {
		if (q-buf>=limit-1) {
			break;
		} else if (*p=='\n') { 
			*(q++)='\\';
			*(q++)='n';
		} else if (*p=='\r') { 
			*(q++)='\\';
			*(q++)='r';
		} else if (*p=='|') { 
			*(q++)='\\';
			*(q++)='|';
		} else if (*p=='\\') { 
			*(q++)='\\';
			*(q++)='\\';
		} else { 
			*(q++)=*p;
		}
	}
	*q='\0';
	return (q-buf);
}

bool neowiz::descInputBinds(sqlrcursor_svr *cursor, char *buf, int limit) {

	char		*c=buf;	
	int		remain_len=limit;
	int		write_len=0;
	static char	bindstrbuf[512+1];

	*c=0;

	// fill the buffers
	for (uint16_t i=0; i<cursor->inbindcount; i++) {

		bindvar_svr	*bv=&(cursor->inbindvars[i]);
	
		write_len=snprintf(c,remain_len,"[%s => ",bv->variable);
		c+=write_len;

		remain_len-=write_len;
		if (remain_len<=0) {
			return false;
		}

		if (bv->type==NULL_BIND) {
			write_len=snprintf(c,remain_len,"NULL]");
		} else if (bv->type==STRING_BIND) {
			strescape(bv->value.stringval,bindstrbuf,512);
			write_len=snprintf(c,remain_len,"'%s']",bindstrbuf);
		} else if (bv->type==INTEGER_BIND) {
			write_len=snprintf(c,remain_len,"'%lld']",
						bv->value.integerval);
		} else if (bv->type==DOUBLE_BIND) {
			write_len=snprintf(c,remain_len,"%lf]",
						bv->value.doubleval.value);
		} else if (bv->type==BLOB_BIND || bv->type==CLOB_BIND) {
			write_len=snprintf(c,remain_len,"LOB]");
		}

		c+=write_len;
		remain_len-=write_len;

		if (remain_len<=0) {
			return false;
		}
	}
	return true;
}
