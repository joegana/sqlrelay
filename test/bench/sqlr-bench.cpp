// Copyright (c) 2014  David Muse
// See the file COPYING for more information
#include <rudiments/commandline.h>
#include <rudiments/process.h>
#include <rudiments/stdio.h>
#include <rudiments/signalclasses.h>
#include <rudiments/dictionary.h>
#include <rudiments/linkedlist.h>
#include <rudiments/file.h>
#include <rudiments/permissions.h>
#include <rudiments/dynamiclib.h>

// for system()
#include <stdlib.h>

#include "sqlrbench.h"

#define ORACLE_SID "(DESCRIPTION = (ADDRESS = (PROTOCOL = TCP)(HOST = oracle)(PORT = 1521)) (CONNECT_DATA = (SERVER = DEDICATED) (SERVICE_NAME = ora1)))"

void shutDown(int32_t signum);
void graphStats(const char *graph, const char *db,
		dictionary< float, linkedlist< float > *> *stats);

sqlrbench	*bm;

int main(int argc, const char **argv) {

	// process the command line
	commandline	cmdl(argc,argv);

	// usage info
	if (cmdl.found("help") || cmdl.found("h")) {
		stdoutput.printf(
			"usage: sqlr-bench \\\n"
			"	[-db db2|informix|firebird|freetds|mysql|"
			"oracle|postgresql|sap|sqlite] \\\n"
			"	[-dbconnectstring dbconnectstring] \\\n"
			"	[-sqlrconnectstring sqlrconnectstring] \\\n"
			"	[-queries total-query-count] \\\n"
			"	[-rows rows-per-query] \\\n"
			"	[-cols columns-per-row] \\\n"
			"	[-colsize characters-per-column] \\\n"
			"	[-samples samples-per-test] \\\n"
			"	[-rsbs result-set-buffer-size] \\\n"
			"	[-dbonly|-sqlrelayonly] \\\n"
			"	[-debug] \\\n"
			"	[-graph graph-file-name]\n");
		process::exit(1);
	}

	// default parameters
	const char	*db="oracle";
	const char	*dbconnectstring=NULL;
	const char	*sqlrconnectstring=NULL;
	uint64_t	queries=30;
	uint64_t	rows=256;
	uint32_t	cols=16;
	uint32_t	colsize=32;
	uint16_t	samples=10;
	uint64_t	rsbs=0;
	bool		dbonly=false;
	bool		sqlrelayonly=false;
	bool		debug=false;
	const char	*graph=NULL;

	// override defaults with command line parameters
	if (cmdl.found("db")) {
		db=cmdl.getValue("db");
	}
	if (cmdl.found("dbconnectstring")) {
		dbconnectstring=cmdl.getValue("dbconnectstring");
	}
	if (cmdl.found("sqlrconnectstring")) {
		sqlrconnectstring=cmdl.getValue("sqlrconnectstring");
	}
	if (cmdl.found("queries")) {
		queries=charstring::toInteger(cmdl.getValue("queries"));
	}
	if (cmdl.found("rows")) {
		rows=charstring::toInteger(cmdl.getValue("rows"));
	}
	if (cmdl.found("cols")) {
		cols=charstring::toInteger(cmdl.getValue("cols"));
	}
	if (cmdl.found("colsize")) {
		colsize=charstring::toInteger(cmdl.getValue("colsize"));
	}
	if (cmdl.found("samples")) {
		samples=charstring::toInteger(cmdl.getValue("samples"));
	}
	if (cmdl.found("rsbs")) {
		rsbs=charstring::toInteger(cmdl.getValue("rsbs"));
	}
	if (cmdl.found("dbonly")) {
		dbonly=true;
	}
	if (cmdl.found("sqlrelayonly")) {
		sqlrelayonly=true;
	}
	if (cmdl.found("debug")) {
		debug=true;
	}
	stringbuffer	graphname;
	if (cmdl.found("graph")) {
		graph=cmdl.getValue("graph");
		graphname.append(graph);
		if (charstring::compare(
			charstring::findFirst(graph,".png"),".png")) {
			graphname.append(".png");
		}
	} else {
		graphname.append(db)->append(".png");
	}
	graph=graphname.getString();

	// handle signals
	bm=NULL;
	process::handleShutDown(shutDown);
	process::handleCrash(shutDown);

	// init stats
	dictionary< float, linkedlist< float > *>	stats;

	// for each database...

	// first time for the real db, second time for sqlrelay...
	bool		shutdown=false;
	uint16_t	start=(sqlrelayonly)?1:0;
	uint16_t	end=(dbonly)?1:2;
	for (uint16_t which=start; which<end && !shutdown; which++) {

		if (!which) {
			stdoutput.printf("\nbenchmarking "
						"%s directly:\n\n",db);
		} else {
			stdoutput.printf("\nbenchmarking "
						"%s via sqlrelay:\n\n",db);
		}

		// default connect strings
		if (which) {
			if (!sqlrconnectstring) {
				sqlrconnectstring=
					"host=localhost;port=9000;"
					"socket=/tmp/test.socket;"
					"user=test;password=test;"
					"debug=no";
			}
		} else if (!charstring::compare(db,"db2")) {
			if (!dbconnectstring) {
				dbconnectstring=
					"db=testdb;lang=C;"
					"user=db2inst1;"
					"password=testpassword;";
			}
		} else if (!charstring::compare(db,"informix")) {
			if (!dbconnectstring) {
				dbconnectstring=
					"informixdir=/opt/informix;"
					"servername=ol_informix1210;"
					"db=testdb;"
					"user=testuser;"
					"password=testpassword;";
			}
		} else if (!charstring::compare(db,"firebird")) {
			if (!dbconnectstring) {
				dbconnectstring=
					"user=testuser;password=testpassword;"
					"db=firebird:"
					"/opt/firebird/testdb.gdb;"
					"dialect=3";
			}
		} else if (!charstring::compare(db,"freetds")) {
			if (!dbconnectstring) {
				dbconnectstring=
					"sybase=/etc;"
					"server=server;db=testdb;"
					"user=testuser;password=testpassword;";
			}
		} else if (!charstring::compare(db,"mysql")) {
			if (!dbconnectstring) {
				dbconnectstring=
				"host=mysql;db=testdb;"
				"user=testuser;password=testpassword;"
				;
			}
		} else if (!charstring::compare(db,"mysqlssl")) {
			if (!dbconnectstring) {
				dbconnectstring=
				"host=mysql;db=testdb;"
				"user=testuser;password=testpassword;"
				"sslca=/etc/mysql-ssl/ca-cert.pem;"
				"sslcert=/etc/mysql-ssl/client-cert.pem;"
				"sslkey=/etc/mysql-ssl/client-key.pem";
			}
		} else if (!charstring::compare(db,"oracle") ||
				!charstring::compare(db,"oracle8")) {
			if (!dbconnectstring) {
				dbconnectstring=
					"sid=" ORACLE_SID ";"
					"user=testuser;password=testpassword;";
			}
		} else if (!charstring::compare(db,"postgresql")) {
			if (!dbconnectstring) {
				dbconnectstring=
					"user=testuser;password=testpassword;"
					"db=testdb;host=postgresql;";
			}
		} else if (!charstring::compare(db,"postgresqlssl")) {
			if (!dbconnectstring) {
				dbconnectstring=
					"user=testuser;password=testpassword;"
					"db=testdb;host=postgresql;"
					"sslmode=verify-ca;";
			}
		} else if (!charstring::compare(db,"sqlite")) {
			if (!dbconnectstring) {
				dbconnectstring=
					"db=/usr/local/sqlite/var/testdb;";
			}
		} else if (!charstring::compare(db,"sap") ||
				!charstring::compare(db,"sybase")) {
			if (!dbconnectstring) {
				dbconnectstring=
					"sybase=/opt/sap;lang=en_US;"
					"server=TESTDB;db=testdb;"
					"user=testuser;password=testpassword;";
			}
		}

		// init bench
		dynamiclib	dl;
		stringbuffer	modulename;
		modulename.append(".libs/sqlrbench_");
		modulename.append((which)?"sqlrelay":db)->append(".so");
		if (!dl.open(modulename.getString(),true,true)) {
			stdoutput.printf("failed to load "
					"bench module: %s\n",
					modulename.getString());
			char	*error=dl.getError();
			stdoutput.printf("%s\n",error);
			delete[] error;
			continue;
		}
		stringbuffer	functionname;
		functionname.append("new_")->append((which)?"sqlrelay":db);
		functionname.append("bench");
		sqlrbench	*(*newBm)(const char *,
						const char *,
						uint64_t,
						uint64_t,
						uint32_t,
						uint32_t,
						uint16_t,
						uint64_t,
						bool)=
			(sqlrbench	*(*)(const char *,
						const char *,
						uint64_t,
						uint64_t,
						uint32_t,
						uint32_t,
						uint16_t,
						uint64_t,
						bool))
			dl.getSymbol(functionname.getString());
		if (!newBm) {
			stdoutput.printf("failed to load bench\n");
			char	*error=dl.getError();
			stdoutput.printf("%s\n",error);
			delete[] error;
			continue;
		}

		bm=newBm((which)?sqlrconnectstring:dbconnectstring,
					db,queries,rows,cols,colsize,
					samples,rsbs,debug);
		if (!bm) {
			stdoutput.printf("error creating bench\n");
			continue;
		}

		// run the benchmarks
		shutdown=!bm->run(&stats);

		delete bm;
	}

	// graph stats
	if (!shutdown) {
		graphStats(graph,db,&stats);
	}

	// clean up
	for (linkedlistnode< float > *node=stats.getKeys()->getFirst();
						node; node=node->getNext()) {
		delete stats.getValue(node->getValue());
	}

	// exit
	process::exit(0);
}

void shutDown(int32_t signum) {
	if (bm) {
		bm->shutDown();
	}
}

void graphStats(const char *graph, const char *db,
		dictionary< float, linkedlist< float > *> *stats) {

	if (charstring::isNullOrEmpty(graph)) {
		stdoutput.printf("\nno stats to graph\n");
		return;
	}

	stdoutput.printf("\ngraphing stats to %s...\n",graph);

	// rename db
	if (!charstring::compare(db,"db2")) {
		db="IBM DB2";
	} else if (!charstring::compare(db,"informix")) {
		db="Informix";
	} else if (!charstring::compare(db,"firebird")) {
		db="Firebird";
	} else if (!charstring::compare(db,"freetds")) {
		db="FreeTDS";
	} else if (!charstring::compare(db,"mysql")) {
		db="MySQL";
	} else if (!charstring::compare(db,"oracle") ||
			!charstring::compare(db,"oracle8")) {
		db="Oracle";
	} else if (!charstring::compare(db,"postgresql")) {
		db="PostgreSQL";
	} else if (!charstring::compare(db,"sqlite")) {
		db="SQLite";
	} else if (!charstring::compare(db,"sap") ||
			!charstring::compare(db,"sybase")) {
		db="SAP/Sybase";
	}

	// write out the stats to temp.csv
	file	f;
	f.open("temp.csv",O_WRONLY|O_TRUNC|O_CREAT,
			permissions::evalPermString("rw-r--r--"));

	for (linkedlistnode< float > *node=stats->getKeys()->getFirst();
						node; node=node->getNext()) {
		f.printf("%f",node->getValue());
		linkedlist< float >	*l=stats->getValue(node->getValue());
		for (linkedlistnode< float > *lnode=l->getFirst();
						lnode; lnode=lnode->getNext()) {
			f.printf(",%f",lnode->getValue());
		}
		f.printf("\n");
	}

	// use gnuplot to create temp.png
	stringbuffer	dbvar;
	dbvar.append("db='")->append(db)->append("'");
	const char	*args[]={
		"gnuplot","-e",dbvar.getString(),"plot.gnu",NULL
	};
	pid_t	pid=process::spawn("gnuplot",args,false);
	process::wait(pid);

	// move temp.png to the specified graph file name
	file::rename("temp.png",graph);

	// move temp.csv to a similar file name as the graph
	stringbuffer	tempcsv;
	char	*base=file::basename(graph,".png");
	tempcsv.append(base)->append(".csv");
	delete[] base;
	file::rename("temp.csv",tempcsv.getString());

	stdoutput.printf("done\n");
}