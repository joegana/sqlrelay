// Copyright (c) 2001  David Muse
// See the file COPYING for more information.

#include <sqlrelay/sqlrclient.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

sqlrconnection	*con;
sqlrcursor	*cur;
sqlrconnection	*secondcon;
sqlrcursor	*secondcur;

int	main(int argc, char **argv) {

	const char *bindvars[2]={"var1",NULL};
	const char *bindvals[1]={"testchar3"};
	const char *subvars[2]={"col1",NULL};
	const char *subvalstrings[1]={"testchar"};
	const char * const *cols;
	const char * const *fields;
	int		port;
	const char	*socket;
	int		id;
	const char	*filename;
	uint32_t	*fieldlens;
	int		counter=1;


	for (;;) {

		// instantiation
		con=new sqlrconnection("localhost",9000, 
					"/tmp/test.socket","test","test",0,1,
					true);
		cur=new sqlrcursor(con,true);



		// get database type
		con->identify();

		// ping
		con->ping();

		// drop existing table
		cur->sendQuery("drop table testtable");

		// insert
		cur->sendQuery("create table testtable (testchar char(40))");
		cur->sendQuery("insert into testtable values (NULL)");
		cur->sendQuery("insert into testtable values ('testchar1')");

		// affected rows
		cur->affectedRows();

		// binds
		cur->prepareQuery("insert into testtable values (:var1)");
		cur->inputBind("var1","testchar2");
		cur->executeQuery();
		cur->clearBinds();
		cur->inputBinds(bindvars,bindvals);
		cur->executeQuery();
		cur->clearBinds();
		cur->inputBind("var1","testchar4");
		cur->inputBind("var2","testchar4");
		cur->validateBinds();
		cur->executeQuery();

		// select
		cur->sendQuery("select * from testtable");

		// column info
		cur->colCount();
		cur->getColumnName(0);
		cols=cur->getColumnNames();
		cur->getColumnType((uint32_t)0);
		cur->getColumnType("testchar");
		cur->getColumnLength((uint32_t)0);
		cur->getColumnLength("testchar");
		cur->getLongest((uint32_t)0);
		cur->getLongest("testchar");

		// row info
		cur->rowCount();
		cur->totalRows();
		cur->firstRowIndex();
		cur->endOfResultSet();

		// field info
		cur->getField(0,(uint32_t)0);
		cur->getFieldLength(0,(uint32_t)0);
		cur->getField(0,"testchar");
		cur->getFieldLength(0,"testchar");
		fields=cur->getRow(0);
		fieldlens=cur->getRowLengths(0);

		// substitutions
		cur->prepareQuery("select $(col1) from testtable");
		cur->substitution("col1","testchar");
		cur->executeQuery();

		// array substitutions
		cur->prepareQuery("select $(col1) from testtable");
		cur->substitutions(subvars,subvalstrings);
		cur->executeQuery();
	
		// nulls as nulls/empty strings
		cur->getNullsAsNulls();
		cur->sendQuery("select * from testtable");
		cur->getNullsAsEmptyStrings();
		cur->sendQuery("select * from testtable");

		// result set buffer size
		cur->setResultSetBufferSize(2);
		cur->sendQuery("select * from testtable");
		cur->getResultSetBufferSize();
		cur->setResultSetBufferSize(0);

		// don't get column info
		cur->dontGetColumnInfo();
		cur->sendQuery("select * from testtable");
		cur->getColumnInfo();
		cur->sendQuery("select * from testtable");

		// suspend/resume
		cur->sendQuery("select * from testtable");
		con->suspendSession();
		port=con->getConnectionPort();
		socket=con->getConnectionSocket();
		con->resumeSession(port,socket);
		cur->getField(3,(uint32_t)0);

		// suspend/resume with result set buffer size
		cur->setResultSetBufferSize(2);
		cur->sendQuery("select * from testtable");
		cur->getField(2,(uint32_t)0);
		id=cur->getResultSetId();
		cur->suspendResultSet();
		con->suspendSession();
		port=con->getConnectionPort();
		socket=con->getConnectionSocket();
		con->resumeSession(port,socket);
		cur->resumeResultSet(id);
		cur->firstRowIndex();
		cur->endOfResultSet();
		cur->rowCount();
		cur->getField(3,(uint32_t)0);
		cur->setResultSetBufferSize(0);

		// cache to file
		cur->cacheToFile("cachefile1");
		cur->setCacheTtl(200);
		cur->sendQuery("select * from testtable");
		filename=cur->getCacheFileName();
		if (strcmp(filename,"cachefile1")) {
			printf("%s\n",filename);
			exit(0);
		}
		cur->cacheOff();
		cur->openCachedResultSet(filename);
		cur->getField(3,(uint32_t)0);
		cur->colCount();
		cur->getColumnName(0);
		cols=cur->getColumnNames();

		// cache to file with result set buffer size
		cur->setResultSetBufferSize(2);
		cur->cacheToFile("cachefile1");
		cur->setCacheTtl(200);
		cur->sendQuery("select * from testtable");
		filename=cur->getCacheFileName();
		if (strcmp(filename,"cachefile1")) {
			printf("%s\n",filename);
			exit(0);
		}
		cur->cacheOff();
		cur->openCachedResultSet(filename);
		cur->getField(3,(uint32_t)0);
		cur->setResultSetBufferSize(0);

		// from 1 cache file to another
		cur->cacheToFile("cachefile2");
		cur->openCachedResultSet("cachefile1");
		cur->cacheOff();
		cur->openCachedResultSet("cachefile2");
		cur->getField(3,(uint32_t)0);

		// from 1 cache file to another with result set buffer size
		cur->setResultSetBufferSize(2);
		cur->cacheToFile("cachefile2");
		cur->openCachedResultSet("cachefile1");
		cur->cacheOff();
		cur->openCachedResultSet("cachefile2");
		cur->getField(3,(uint32_t)0);
		cur->setResultSetBufferSize(0);

		// suspend/resume with cache file
		cur->setResultSetBufferSize(2);
		cur->cacheToFile("cachefile1");
		cur->setCacheTtl(200);
		cur->sendQuery("select * from testtable");
		cur->getField(2,(uint32_t)0);
		filename=cur->getCacheFileName();
		if (strcmp(filename,"cachefile1")) {
			printf("%s\n",filename);
			exit(0);
		}
		id=cur->getResultSetId();
		cur->suspendResultSet();
		con->suspendSession();
		port=con->getConnectionPort();
		socket=con->getConnectionSocket();
		con->resumeSession(port,socket);
		cur->resumeCachedResultSet(id,filename);
		cur->firstRowIndex();
		cur->endOfResultSet();
		cur->rowCount();
		cur->getField(3,(uint32_t)0);
		cur->setResultSetBufferSize(0);

		// commit/rollback
		secondcon=new sqlrconnection("localhost",9000,
				"/tmp/test.socket","test","test",0,1);
		secondcur=new sqlrcursor(secondcon);
		secondcur->sendQuery("select count(*) from testtable");
		secondcur->getField(0,(uint32_t)0);
		con->commit();
		secondcur->sendQuery("select count(*) from testtable");
		secondcur->getField(0,(uint32_t)0);
		con->autoCommitOn();
		cur->sendQuery("insert into testtable values ('testchar10')");
		secondcur->sendQuery("select count(*) from testtable");
		secondcur->getField(0,(uint32_t)0);
		con->autoCommitOff();

		delete secondcur;
		delete secondcon;

		// drop existing table
		cur->sendQuery("drop table testtable");

		// invalid queries...
		cur->sendQuery("select * from testtable");
		cur->sendQuery("insert into testtable values (1,2,3,4)");
		cur->sendQuery("create table testtable");

		printf("loop %i\n",counter);
		counter++;

		delete cur;
		delete con;
	}
}
