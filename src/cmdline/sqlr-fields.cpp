// Copyright (c) 1999-2001  David Muse
// See the file COPYING for more information

#include <config.h>
#include <defaults.h>

#include <sqlrelay/sqlrclient.h>
#include <sqlrelay/sqlrutil.h>

#include <rudiments/stringbuffer.h>
#include <rudiments/process.h>
#include <rudiments/stdio.h>

int main(int argc, const char **argv) {

	#include <version.h>

	sqlrcmdline	cmdline(argc,argv);
	sqlrpaths	sqlrpth(&cmdline);
	sqlrconfigs	sqlrcfgs(&sqlrpth);

	const char	*configurl=sqlrpth.getConfigUrl();
	const char	*id=cmdline.getValue("-id");
	const char	*host=cmdline.getValue("-host");
	uint16_t	port=charstring::toInteger(
				(cmdline.found("-port"))?
					cmdline.getValue("-port"):DEFAULT_PORT);
	const char	*socket=cmdline.getValue("-socket");
	const char	*user=cmdline.getValue("-user");
	const char	*password=cmdline.getValue("-password");
	const char	*table=cmdline.getValue("-table");
	bool		debug=cmdline.found("-debug");
	const char	*debugfile=NULL;
	if (debug) {
		debugfile=cmdline.getValue("-debug");
	}

	if (!(charstring::length(id) ||
		charstring::length(host) ||
		charstring::length(socket)) ||
		!(charstring::length(table))) {

		stdoutput.printf("usage: %s-fields -host host -port port -socket socket -table table [-debug [filename]]\n"
			"  or   %s-fields  [-config config] -id id -table table [-debug [filename]]\n",SQLR,SQLR);
		process::exit(1);
	}

	sqlrconfig	*cfg=sqlrcfgs.load(configurl,id);
	if (cfg) {

		// get the host/port/socket/username/password
		host="localhost";
		port=cfg->getDefaultPort();
		socket=cfg->getDefaultSocket();
		linkedlistnode< usercontainer * >	*firstuser=
					cfg->getUserList()->getFirst();
		if (firstuser) {
			usercontainer	*currentnode=firstuser->getValue();
			user=currentnode->getUser();
			password=currentnode->getPassword();
		}
	}

	sqlrconnection	sqlrcon(host,port,socket,user,password,0,1);
	sqlrcursor	sqlrcur(&sqlrcon);

	if (debug) {
		if (debugfile) {
			sqlrcon.setDebugFile(debugfile);
		}
		sqlrcon.debugOn();
	}

	if (sqlrcur.getColumnList(table,NULL)) {
		for (uint64_t j=0; j<sqlrcur.rowCount(); j++) {
			if (j>0) {
				stdoutput.printf(",");
			}
			stdoutput.printf("%s",sqlrcur.getField(j,(uint32_t)0));
		}
		stdoutput.printf("\n");
	}

	process::exit(0);
}
