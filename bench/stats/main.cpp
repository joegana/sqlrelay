// Copyright (c) 2014  David Muse
// See the file COPYING for more information
#include <rudiments/commandline.h>
#include <rudiments/process.h>
#include <rudiments/stdio.h>
#include <rudiments/signalclasses.h>

#include "bench.h"

#include "db2bench.h"
#include "firebirdbench.h"
#include "freetdsbench.h"
#include "mysqlbench.h"
#include "oraclebench.h"
#include "postgresqlbench.h"
#include "sqlitebench.h"
#include "sybasebench.h"
#include "sqlrelaybench.h"

#define ORACLE_SID "(DESCRIPTION = (ADDRESS = (PROTOCOL = TCP)(HOST = db64.firstworks.com)(PORT = 1521)) (CONNECT_DATA = (SERVER = DEDICATED) (SERVICE_NAME = ora1)))"

benchmarks	*bm;

void shutDown(int32_t signum) {
	if (bm) {
		bm->shutDown();
	}
}

int main(int argc, const char **argv) {

	// process the command line
	commandline	cmdl(argc,argv);

	// usage info
	if (cmdl.found("help") || cmdl.found("h")) {
		stdoutput.printf(
			"usage: sqlr-bench \\\n"
			"	-db [db] \\\n"
			"	-queries [total-query-count] \\\n"
			"	-rows [rows-per-query] \\\n"
			"	-cols [columns-per-row] \\\n"
			"	-colsize [characters-per-column] \\\n"
			"	-iterations [iterations-per-test] \\\n"
			"	-dbonly|-sqlrelayonly \\n"
			"	-debug\n");
		process::exit(1);
	}

	// default parameters
	const char	*db="oracle";
	uint64_t	queries=20;
	uint64_t	rows=256;
	uint32_t	cols=16;
	uint32_t	colsize=32;
	uint16_t	iterations=10;
	bool		dbonly=false;
	bool		sqlrelayonly=false;
	bool		debug=false;

	// override defaults with command line parameters
	if (cmdl.found("db")) {
		db=cmdl.getValue("db");
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
	if (cmdl.found("iterations")) {
		iterations=charstring::toInteger(cmdl.getValue("iterations"));
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

	// handle signals
	bm=NULL;
	process::handleShutDown(shutDown);
	process::handleCrash(shutDown);

	// for each database...
	bool	error=false;

	// first time for the real db, second time for sqlrelay...
	uint16_t	start=(sqlrelayonly)?1:0;
	uint16_t	end=(dbonly)?1:2;
	for (uint16_t which=start; which<end && !error; which++) {

		if (!which) {
			stdoutput.printf("benchmarking %s\n",db);
		} else {
			stdoutput.printf("benchmarking sqlrelay-%s\n",db);
		}

		// init benchmarks
		delete bm;
		if (which) {
			bm=new sqlrelaybenchmarks(
					"host=localhost;port=9000;"
					"socket=/tmp/test.socket;"
					"user=test;password=test;"
					"debug=no",
					db,queries,rows,
					cols,colsize,iterations,debug);
		} else if (!charstring::compare(db,"db2")) {
			bm=new db2benchmarks(
					"db=testdb;lang=C;"
					"user=db2inst1;password=1qazxdr5;",
					db,queries,rows,
					cols,colsize,iterations,debug);
		} else if (!charstring::compare(db,"firebird")) {
			bm=new firebirdbenchmarks(
					"user=testuser;password=testpassword;"
					"db=db64.firstworks.com:"
					"/opt/firebird/testdb.gdb;"
					"dialect=3",
					db,queries,rows,
					cols,colsize,iterations,debug);
		} else if (!charstring::compare(db,"freetds")) {
			bm=new freetdsbenchmarks(
					"sybase=/usr/localfreetds/etc;"
					"server=DB64;db=testdb;"
					"user=testuser;password=testpassword;",
					db,queries,rows,
					cols,colsize,iterations,debug);
		} else if (!charstring::compare(db,"mysql")) {
			bm=new mysqlbenchmarks(
					"host=db64;db=testdb;"
					"user=testuser;password=testpassword;",
					db,queries,rows,
					cols,colsize,iterations,debug);
		} else if (!charstring::compare(db,"oracle")) {
			bm=new oraclebenchmarks(
					"sid="ORACLE_SID";"
					"user=testuser;password=testpassword;",
					db,queries,rows,
					cols,colsize,iterations,debug);
		} else if (!charstring::compare(db,"postgresql")) {
			bm=new postgresqlbenchmarks(
					"user=testuser;password=testpassword;"
					"db=testdb;host=db64.firstworks.com;",
					db,queries,rows,
					cols,colsize,iterations,debug);
		} else if (!charstring::compare(db,"sqlite")) {
			bm=new sqlitebenchmarks(
					"db=/usr/local/sqlite/var/testdb;",
					db,queries,rows,
					cols,colsize,iterations,debug);
		} else if (!charstring::compare(db,"sybase")) {
			bm=new sybasebenchmarks(
					"sybase=/opt/sybase;lang=en_US;"
					"server=TESTDB;db=testdb;"
					"user=testuser;password=testpassword;",
					db,queries,rows,
					cols,colsize,iterations,debug);
		}
		if (!bm) {
			stdoutput.printf("error creating benchmarks\n");
			continue;
		}

		// run the benchmarks
		bm->run();
	}

	// exit
	process::exit(0);
}
