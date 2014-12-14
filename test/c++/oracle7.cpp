// Copyright (c) 2001  David Muse
// See the file COPYING for more information.

#include <rudiments/charstring.h>
#include <sqlrelay/sqlrclient.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

sqlrconnection	*con;
sqlrcursor	*cur;

void checkSuccess(const char *value, const char *success) {

	if (!success) {
		if (!value) {
			printf("success ");
			return;
		} else {
			printf("%s!=%s\n",value,success);
			printf("failure ");
			delete cur;
			delete con;
			exit(0);
		}
	}

	if (!charstring::compare(value,success)) {
		printf("success ");
	} else {
		printf("%s!=%s\n",value,success);
		printf("failure ");
		delete cur;
		delete con;
		exit(0);
	}
}

void checkSuccess(const char *value, const char *success, size_t length) {

	if (!success) {
		if (!value) {
			printf("success ");
			return;
		} else {
			printf("%s!=%s\n",value,success);
			printf("failure ");
			delete cur;
			delete con;
			exit(0);
		}
	}

	if (!strncmp(value,success,length)) {
		printf("success ");
	} else {
		printf("%s!=%s\n",value,success);
		printf("failure ");
		delete cur;
		delete con;
		exit(0);
	}
}

void checkSuccess(int value, int success) {

	if (value==success) {
		printf("success ");
	} else {
		printf("%d!=%d\n",value,success);
		printf("failure ");
		delete cur;
		delete con;
		exit(0);
	}
}

void checkSuccess(double value, double success) {

	if (value==success) {
		printf("success ");
	} else {
		printf("%f!=%f\n",value,success);
		printf("failure ");
		delete cur;
		delete con;
		exit(0);
	}
}

int	main(int argc, char **argv) {

	const char	*bindvars[6]={"1","2","3","4","5",NULL};
	const char	*bindvals[5]={"4","testchar4","testvarchar4","01-JAN-04","testlong4"};
	const char	*subvars[4]={"var1","var2","var3",NULL};
	const char	*subvalstrings[3]={"hi","hello","bye"};
	int64_t		subvallongs[3]={1,2,3};
	double		subvaldoubles[3]={10.55,10.556,10.5556};
	uint32_t	precs[3]={4,5,6};
	uint32_t	scales[3]={2,3,4};
	int64_t		numvar;
	const char	*stringvar;
	double		floatvar;
	const char * const *cols;
	const char * const *fields;
	uint16_t	port;
	const char	*socket;
	uint16_t	id;
	const char	*filename;
	const char	*arraybindvars[6]={"var1","var2","var3","var4","var5",NULL};
	const char	*arraybindvals[5]={"7","testchar7","testvarchar7","01-JAN-07","testlong7"};
	uint32_t	*fieldlens;

	// instantiation
	con=new sqlrconnection("sqlrserver",9000,"/tmp/test.socket",
							"test","test",0,1);
	cur=new sqlrcursor(con);

	// get database type
	printf("IDENTIFY: \n");
	checkSuccess(con->identify(),"oracle8");
	printf("\n");

	// ping
	printf("PING: \n");
	checkSuccess(con->ping(),1);
	printf("\n");

	// drop existing table
	cur->sendQuery("drop table testtable");

	printf("CREATE TEMPTABLE: \n");
	checkSuccess(cur->sendQuery("create table testtable (testnumber number, testchar char(40), testvarchar varchar2(40), testdate date, testlong long)"),1);
	printf("\n");

	printf("INSERT: \n");
	checkSuccess(cur->sendQuery("insert into testtable values (1,'testchar1','testvarchar1','01-JAN-01','testlong1')"),1);
	checkSuccess(cur->countBindVariables(),0);
	printf("\n");

	printf("AFFECTED ROWS: \n");
	checkSuccess(cur->affectedRows(),1);
	printf("\n");

	printf("BIND BY POSITION: \n");
	cur->prepareQuery("insert into testtable values (:var1,:var2,:var3,:var4,:var5)");
	checkSuccess(cur->countBindVariables(),5);
	cur->inputBind("1",2);
	cur->inputBind("2","testchar2");
	cur->inputBind("3","testvarchar2");
	cur->inputBind("4",2,1,1,0,0,0,0,NULL);
	cur->inputBind("5","testlong2");
	checkSuccess(cur->executeQuery(),1);
	cur->clearBinds();
	cur->inputBind("1",3);
	cur->inputBind("2","testchar3");
	cur->inputBind("3","testvarchar3");
	cur->inputBind("4",3,1,1,0,0,0,0,NULL);
	cur->inputBind("5","testlong3");
	checkSuccess(cur->executeQuery(),1);
	printf("\n");

	printf("ARRAY OF BINDS BY POSITION: \n");
	cur->clearBinds();
	cur->inputBinds(bindvars,bindvals);
	checkSuccess(cur->executeQuery(),1);
	printf("\n");

	printf("BIND BY NAME: \n");
	cur->prepareQuery("insert into testtable values (:var1,:var2,:var3,:var4,:var5)");
	cur->inputBind("var1",5);
	cur->inputBind("var2","testchar5");
	cur->inputBind("var3","testvarchar5");
	cur->inputBind("var4",5,1,1,0,0,0,0,NULL);
	cur->inputBind("var5","testlong5");
	checkSuccess(cur->executeQuery(),1);
	cur->clearBinds();
	cur->inputBind("var1",6);
	cur->inputBind("var2","testchar6");
	cur->inputBind("var3","testvarchar6");
	cur->inputBind("var4",6,1,1,0,0,0,0,NULL);
	cur->inputBind("var5","testlong6");
	checkSuccess(cur->executeQuery(),1);
	printf("\n");

	printf("ARRAY OF BINDS BY NAME: \n");
	cur->clearBinds();
	cur->inputBinds(arraybindvars,arraybindvals);
	checkSuccess(cur->executeQuery(),1);
	printf("\n");

	printf("BIND BY NAME WITH VALIDATION: \n");
	cur->clearBinds();
	cur->inputBind("var1",8);
	cur->inputBind("var2","testchar8");
	cur->inputBind("var3","testvarchar8");
	cur->inputBind("var4",8,1,1,0,0,0,0,NULL);
	cur->inputBind("var5","testlong8");
	cur->inputBind("var9","junkvalue");
	cur->validateBinds();
	checkSuccess(cur->executeQuery(),1);
	printf("\n");

	printf("OUTPUT BIND BY NAME: \n");
	cur->prepareQuery("begin  :numvar:=1; :stringvar:='hello'; :floatvar:=2.5; :datevar:='03-FEB-01'; end;");
	cur->defineOutputBindInteger("numvar");
	cur->defineOutputBindString("stringvar",10);
	cur->defineOutputBindDouble("floatvar");
	cur->defineOutputBindDate("datevar");
	checkSuccess(cur->executeQuery(),1);
	numvar=cur->getOutputBindInteger("numvar");
	stringvar=cur->getOutputBindString("stringvar");
	floatvar=cur->getOutputBindDouble("floatvar");
	int16_t	year=0;
	int16_t	month=0;
	int16_t	day=0;
	int16_t	hour=0;
	int16_t	minute=0;
	int16_t	second=0;
	int32_t	microsecond=0;
	const char	*tz=NULL;
	cur->getOutputBindDate("datevar",&year,&month,&day,
					&hour,&minute,&second,&microsecond,&tz);
	checkSuccess(numvar,1);
	checkSuccess(stringvar,"hello");
	checkSuccess(floatvar,2.5);
	checkSuccess(year,2001);
	checkSuccess(month,2);
	checkSuccess(day,3);
	checkSuccess(hour,0);
	checkSuccess(minute,0);
	checkSuccess(second,0);
	checkSuccess(microsecond,0);
	checkSuccess(tz,"");
	printf("\n");

	printf("OUTPUT BIND BY POSITION: \n");
	cur->clearBinds();
	cur->defineOutputBindInteger("1");
	cur->defineOutputBindString("2",10);
	cur->defineOutputBindDouble("3");
	cur->defineOutputBindDate("4");
	checkSuccess(cur->executeQuery(),1);
	numvar=cur->getOutputBindInteger("1");
	stringvar=cur->getOutputBindString("2");
	floatvar=cur->getOutputBindDouble("3");
	cur->getOutputBindDate("datevar",&year,&month,&day,
					&hour,&minute,&second,&microsecond,&tz);
	checkSuccess(numvar,1);
	checkSuccess(stringvar,"hello");
	checkSuccess(floatvar,2.5);
	checkSuccess(year,2001);
	checkSuccess(month,2);
	checkSuccess(day,3);
	checkSuccess(hour,0);
	checkSuccess(minute,0);
	checkSuccess(second,0);
	checkSuccess(microsecond,0);
	checkSuccess(tz,"");
	printf("\n");

	printf("OUTPUT BIND BY NAME WITH VALIDATION: \n");
	cur->clearBinds();
	cur->defineOutputBindInteger("numvar");
	cur->defineOutputBindString("stringvar",10);
	cur->defineOutputBindDouble("floatvar");
	cur->defineOutputBindDate("datevar");
	cur->defineOutputBindString("dummyvar",10);
	cur->validateBinds();
	checkSuccess(cur->executeQuery(),1);
	numvar=cur->getOutputBindInteger("numvar");
	stringvar=cur->getOutputBindString("stringvar");
	floatvar=cur->getOutputBindDouble("floatvar");
	cur->getOutputBindDate("datevar",&year,&month,&day,
					&hour,&minute,&second,&microsecond,&tz);
	checkSuccess(numvar,1);
	checkSuccess(stringvar,"hello");
	checkSuccess(floatvar,2.5);
	checkSuccess(year,2001);
	checkSuccess(month,2);
	checkSuccess(day,3);
	checkSuccess(hour,0);
	checkSuccess(minute,0);
	checkSuccess(second,0);
	checkSuccess(microsecond,0);
	checkSuccess(tz,"");
	printf("\n");

	printf("SELECT: \n");
	checkSuccess(cur->sendQuery("select * from testtable order by testnumber"),1);
	printf("\n");

	printf("COLUMN COUNT: \n");
	checkSuccess(cur->colCount(),5);
	printf("\n");

	printf("COLUMN NAMES: \n");
	checkSuccess(cur->getColumnName(0),"TESTNUMBER");
	checkSuccess(cur->getColumnName(1),"TESTCHAR");
	checkSuccess(cur->getColumnName(2),"TESTVARCHAR");
	checkSuccess(cur->getColumnName(3),"TESTDATE");
	checkSuccess(cur->getColumnName(4),"TESTLONG");
	cols=cur->getColumnNames();
	checkSuccess(cols[0],"TESTNUMBER");
	checkSuccess(cols[1],"TESTCHAR");
	checkSuccess(cols[2],"TESTVARCHAR");
	checkSuccess(cols[3],"TESTDATE");
	checkSuccess(cols[4],"TESTLONG");
	printf("\n");

	printf("COLUMN TYPES: \n");
	checkSuccess(cur->getColumnType((uint32_t)0),"NUMBER");
	checkSuccess(cur->getColumnType("testnumber"),"NUMBER");
	checkSuccess(cur->getColumnType(1),"CHAR");
	checkSuccess(cur->getColumnType("testchar"),"CHAR");
	checkSuccess(cur->getColumnType(2),"VARCHAR2");
	checkSuccess(cur->getColumnType("testvarchar"),"VARCHAR2");
	checkSuccess(cur->getColumnType(3),"DATE");
	checkSuccess(cur->getColumnType("testdate"),"DATE");
	checkSuccess(cur->getColumnType(4),"LONG");
	checkSuccess(cur->getColumnType("testlong"),"LONG");
	printf("\n");

	printf("COLUMN LENGTH: \n");
	checkSuccess(cur->getColumnLength((uint32_t)0),22);
	checkSuccess(cur->getColumnLength("testnumber"),22);
	checkSuccess(cur->getColumnLength(1),40);
	checkSuccess(cur->getColumnLength("testchar"),40);
	checkSuccess(cur->getColumnLength(2),40);
	checkSuccess(cur->getColumnLength("testvarchar"),40);
	checkSuccess(cur->getColumnLength(3),7);
	checkSuccess(cur->getColumnLength("testdate"),7);
	checkSuccess(cur->getColumnLength(4),0);
	checkSuccess(cur->getColumnLength("testlong"),0);
	printf("\n");

	printf("LONGEST COLUMN: \n");
	checkSuccess(cur->getLongest((uint32_t)0),1);
	checkSuccess(cur->getLongest("testnumber"),1);
	checkSuccess(cur->getLongest(1),40);
	checkSuccess(cur->getLongest("testchar"),40);
	checkSuccess(cur->getLongest(2),12);
	checkSuccess(cur->getLongest("testvarchar"),12);
	checkSuccess(cur->getLongest(3),9);
	checkSuccess(cur->getLongest("testdate"),9);
	checkSuccess(cur->getLongest(4),9);
	checkSuccess(cur->getLongest("testlong"),9);
	printf("\n");

	printf("ROW COUNT: \n");
	checkSuccess(cur->rowCount(),8);
	printf("\n");

	printf("TOTAL ROWS: \n");
	checkSuccess(cur->totalRows(),0);
	printf("\n");

	printf("FIRST ROW INDEX: \n");
	checkSuccess(cur->firstRowIndex(),0);
	printf("\n");

	printf("END OF RESULT SET: \n");
	checkSuccess(cur->endOfResultSet(),1);
	printf("\n");

	printf("FIELDS BY INDEX: \n");
	checkSuccess(cur->getField(0,(uint32_t)0),"1");
	checkSuccess(cur->getField(0,1),"testchar1                               ");
	checkSuccess(cur->getField(0,2),"testvarchar1");
	checkSuccess(cur->getField(0,3),"01-JAN-01");
	checkSuccess(cur->getField(0,4),"testlong1");
	printf("\n");
	checkSuccess(cur->getField(7,(uint32_t)0),"8");
	checkSuccess(cur->getField(7,1),"testchar8                               ");
	checkSuccess(cur->getField(7,2),"testvarchar8");
	checkSuccess(cur->getField(7,3),"01-JAN-08");
	checkSuccess(cur->getField(7,4),"testlong8");
	printf("\n");

	printf("FIELD LENGTHS BY INDEX: \n");
	checkSuccess(cur->getFieldLength(0,(uint32_t)0),1);
	checkSuccess(cur->getFieldLength(0,1),40);
	checkSuccess(cur->getFieldLength(0,2),12);
	checkSuccess(cur->getFieldLength(0,3),9);
	checkSuccess(cur->getFieldLength(0,4),9);
	printf("\n");
	checkSuccess(cur->getFieldLength(7,(uint32_t)0),1);
	checkSuccess(cur->getFieldLength(7,1),40);
	checkSuccess(cur->getFieldLength(7,2),12);
	checkSuccess(cur->getFieldLength(7,3),9);
	checkSuccess(cur->getFieldLength(7,4),9);
	printf("\n");

	printf("FIELDS BY NAME: \n");
	checkSuccess(cur->getField(0,"testnumber"),"1");
	checkSuccess(cur->getField(0,"testchar"),"testchar1                               ");
	checkSuccess(cur->getField(0,"testvarchar"),"testvarchar1");
	checkSuccess(cur->getField(0,"testdate"),"01-JAN-01");
	checkSuccess(cur->getField(0,"testlong"),"testlong1");
	printf("\n");
	checkSuccess(cur->getField(7,"testnumber"),"8");
	checkSuccess(cur->getField(7,"testchar"),"testchar8                               ");
	checkSuccess(cur->getField(7,"testvarchar"),"testvarchar8");
	checkSuccess(cur->getField(7,"testdate"),"01-JAN-08");
	checkSuccess(cur->getField(7,"testlong"),"testlong8");
	printf("\n");

	printf("FIELD LENGTHS BY NAME: \n");
	checkSuccess(cur->getFieldLength(0,"testnumber"),1);
	checkSuccess(cur->getFieldLength(0,"testchar"),40);
	checkSuccess(cur->getFieldLength(0,"testvarchar"),12);
	checkSuccess(cur->getFieldLength(0,"testdate"),9);
	checkSuccess(cur->getFieldLength(0,"testlong"),9);
	printf("\n");
	checkSuccess(cur->getFieldLength(7,"testnumber"),1);
	checkSuccess(cur->getFieldLength(7,"testchar"),40);
	checkSuccess(cur->getFieldLength(7,"testvarchar"),12);
	checkSuccess(cur->getFieldLength(7,"testdate"),9);
	checkSuccess(cur->getFieldLength(7,"testlong"),9);
	printf("\n");

	printf("FIELDS BY ARRAY: \n");
	fields=cur->getRow(0);
	checkSuccess(fields[0],"1");
	checkSuccess(fields[1],"testchar1                               ");
	checkSuccess(fields[2],"testvarchar1");
	checkSuccess(fields[3],"01-JAN-01");
	checkSuccess(fields[4],"testlong1");
	printf("\n");

	printf("FIELD LENGTHS BY ARRAY: \n");
	fieldlens=cur->getRowLengths(0);
	checkSuccess(fieldlens[0],1);
	checkSuccess(fieldlens[1],40);
	checkSuccess(fieldlens[2],12);
	checkSuccess(fieldlens[3],9);
	checkSuccess(fieldlens[4],9);
	printf("\n");

	printf("INDIVIDUAL SUBSTITUTIONS: \n");
	cur->prepareQuery("select $(var1),'$(var2)',$(var3) from dual");
	cur->substitution("var1",1);
	cur->substitution("var2","hello");
	cur->substitution("var3",10.5556,6,4);
	checkSuccess(cur->executeQuery(),1);
	printf("\n");

	printf("FIELDS: \n");
	checkSuccess(cur->getField(0,(uint32_t)0),"1");
	checkSuccess(cur->getField(0,1),"hello");
	checkSuccess(cur->getField(0,2),"10.5556");
	printf("\n");

	printf("OUTPUT BIND: \n");
	cur->prepareQuery("begin :var1:='hello'; end;");
	cur->defineOutputBindString("var1",10);
	checkSuccess(cur->executeQuery(),1);
	checkSuccess(cur->getOutputBindString("var1"),"hello");
	printf("\n");

	printf("ARRAY SUBSTITUTIONS: \n");
	cur->prepareQuery("select $(var1),$(var2),$(var3) from dual");
	cur->substitutions(subvars,subvallongs);
	checkSuccess(cur->executeQuery(),1);
	printf("\n");
	
	printf("FIELDS: \n");
	checkSuccess(cur->getField(0,(uint32_t)0),"1");
	checkSuccess(cur->getField(0,1),"2");
	checkSuccess(cur->getField(0,2),"3");
	printf("\n");
	
	printf("ARRAY SUBSTITUTIONS: \n");
	cur->prepareQuery("select '$(var1)','$(var2)','$(var3)' from dual");
	cur->substitutions(subvars,subvalstrings);
	checkSuccess(cur->executeQuery(),1);
	printf("\n");

	printf("FIELDS: \n");
	checkSuccess(cur->getField(0,(uint32_t)0),"hi");
	checkSuccess(cur->getField(0,1),"hello");
	checkSuccess(cur->getField(0,2),"bye");
	printf("\n");

	printf("ARRAY SUBSTITUTIONS: \n");
	cur->prepareQuery("select $(var1),$(var2),$(var3) from dual");
	cur->substitutions(subvars,subvaldoubles,precs,scales);
	checkSuccess(cur->executeQuery(),1);
	printf("\n");

	printf("FIELDS: \n");
	checkSuccess(cur->getField(0,(uint32_t)0),"10.55");
	checkSuccess(cur->getField(0,1),"10.556");
	checkSuccess(cur->getField(0,2),"10.5556");
	printf("\n");

	printf("NULLS as Nulls: \n");
	cur->getNullsAsNulls();
	checkSuccess(cur->sendQuery("select NULL,1,NULL from dual"),1);
	checkSuccess(cur->getField(0,(uint32_t)0),NULL);
	checkSuccess(cur->getField(0,1),"1");
	checkSuccess(cur->getField(0,2),NULL);
	cur->getNullsAsEmptyStrings();
	checkSuccess(cur->sendQuery("select NULL,1,NULL from dual"),1);
	checkSuccess(cur->getField(0,(uint32_t)0),"");
	checkSuccess(cur->getField(0,1),"1");
	checkSuccess(cur->getField(0,2),"");
	cur->getNullsAsNulls();
	printf("\n");

	printf("RESULT SET BUFFER SIZE: \n");
	checkSuccess(cur->getResultSetBufferSize(),0);
	cur->setResultSetBufferSize(2);
	checkSuccess(cur->sendQuery("select * from testtable order by testnumber"),1);
	checkSuccess(cur->getResultSetBufferSize(),2);
	printf("\n");
	checkSuccess(cur->firstRowIndex(),0);
	checkSuccess(cur->endOfResultSet(),0);
	checkSuccess(cur->rowCount(),2);
	checkSuccess(cur->getField(0,(uint32_t)0),"1");
	checkSuccess(cur->getField(1,(uint32_t)0),"2");
	checkSuccess(cur->getField(2,(uint32_t)0),"3");
	checkSuccess(cur->firstRowIndex(),2);
	checkSuccess(cur->endOfResultSet(),0);
	checkSuccess(cur->rowCount(),4);
	checkSuccess(cur->getField(6,(uint32_t)0),"7");
	checkSuccess(cur->getField(7,(uint32_t)0),"8");
	printf("\n");
	checkSuccess(cur->firstRowIndex(),6);
	checkSuccess(cur->endOfResultSet(),0);
	checkSuccess(cur->rowCount(),8);
	checkSuccess(cur->getField(8,(uint32_t)0),NULL);
	printf("\n");
	checkSuccess(cur->firstRowIndex(),8);
	checkSuccess(cur->endOfResultSet(),1);
	checkSuccess(cur->rowCount(),8);
	printf("\n");

	printf("DONT GET COLUMN INFO: \n");
	cur->dontGetColumnInfo();
	checkSuccess(cur->sendQuery("select * from testtable order by testnumber"),1);
	checkSuccess(cur->getColumnName(0),NULL);
	checkSuccess(cur->getColumnLength((uint32_t)0),0);
	checkSuccess(cur->getColumnType((uint32_t)0),NULL);
	cur->getColumnInfo();
	checkSuccess(cur->sendQuery("select * from testtable order by testnumber"),1);
	checkSuccess(cur->getColumnName(0),"TESTNUMBER");
	checkSuccess(cur->getColumnLength((uint32_t)0),22);
	checkSuccess(cur->getColumnType((uint32_t)0),"NUMBER");
	printf("\n");

	printf("SUSPENDED SESSION: \n");
	checkSuccess(cur->sendQuery("select * from testtable order by testnumber"),1);
	cur->suspendResultSet();
	checkSuccess(con->suspendSession(),1);
	port=con->getConnectionPort();
	socket=strdup(con->getConnectionSocket());
	checkSuccess(con->resumeSession(port,socket),1);
	printf("\n");
	checkSuccess(cur->getField(0,(uint32_t)0),"1");
	checkSuccess(cur->getField(1,(uint32_t)0),"2");
	checkSuccess(cur->getField(2,(uint32_t)0),"3");
	checkSuccess(cur->getField(3,(uint32_t)0),"4");
	checkSuccess(cur->getField(4,(uint32_t)0),"5");
	checkSuccess(cur->getField(5,(uint32_t)0),"6");
	checkSuccess(cur->getField(6,(uint32_t)0),"7");
	checkSuccess(cur->getField(7,(uint32_t)0),"8");
	printf("\n");
	checkSuccess(cur->sendQuery("select * from testtable order by testnumber"),1);
	cur->suspendResultSet();
	checkSuccess(con->suspendSession(),1);
	port=con->getConnectionPort();
	socket=strdup(con->getConnectionSocket());
	checkSuccess(con->resumeSession(port,socket),1);
	printf("\n");
	checkSuccess(cur->getField(0,(uint32_t)0),"1");
	checkSuccess(cur->getField(1,(uint32_t)0),"2");
	checkSuccess(cur->getField(2,(uint32_t)0),"3");
	checkSuccess(cur->getField(3,(uint32_t)0),"4");
	checkSuccess(cur->getField(4,(uint32_t)0),"5");
	checkSuccess(cur->getField(5,(uint32_t)0),"6");
	checkSuccess(cur->getField(6,(uint32_t)0),"7");
	checkSuccess(cur->getField(7,(uint32_t)0),"8");
	printf("\n");
	checkSuccess(cur->sendQuery("select * from testtable order by testnumber"),1);
	cur->suspendResultSet();
	checkSuccess(con->suspendSession(),1);
	port=con->getConnectionPort();
	socket=strdup(con->getConnectionSocket());
	checkSuccess(con->resumeSession(port,socket),1);
	printf("\n");
	checkSuccess(cur->getField(0,(uint32_t)0),"1");
	checkSuccess(cur->getField(1,(uint32_t)0),"2");
	checkSuccess(cur->getField(2,(uint32_t)0),"3");
	checkSuccess(cur->getField(3,(uint32_t)0),"4");
	checkSuccess(cur->getField(4,(uint32_t)0),"5");
	checkSuccess(cur->getField(5,(uint32_t)0),"6");
	checkSuccess(cur->getField(6,(uint32_t)0),"7");
	checkSuccess(cur->getField(7,(uint32_t)0),"8");
	printf("\n");

	printf("SUSPENDED RESULT SET: \n");
	cur->setResultSetBufferSize(2);
	checkSuccess(cur->sendQuery("select * from testtable order by testnumber"),1);
	checkSuccess(cur->getField(2,(uint32_t)0),"3");
	id=cur->getResultSetId();
	cur->suspendResultSet();
	checkSuccess(con->suspendSession(),1);
	port=con->getConnectionPort();
	socket=strdup(con->getConnectionSocket());
	checkSuccess(con->resumeSession(port,socket),1);
	checkSuccess(cur->resumeResultSet(id),1);
	printf("\n");
	checkSuccess(cur->firstRowIndex(),4);
	checkSuccess(cur->endOfResultSet(),0);
	checkSuccess(cur->rowCount(),6);
	checkSuccess(cur->getField(7,(uint32_t)0),"8");
	printf("\n");
	checkSuccess(cur->firstRowIndex(),6);
	checkSuccess(cur->endOfResultSet(),0);
	checkSuccess(cur->rowCount(),8);
	checkSuccess(cur->getField(8,(uint32_t)0),NULL);
	printf("\n");
	checkSuccess(cur->firstRowIndex(),8);
	checkSuccess(cur->endOfResultSet(),1);
	checkSuccess(cur->rowCount(),8);
	cur->setResultSetBufferSize(0);
	printf("\n");

	printf("CACHED RESULT SET: \n");
	cur->cacheToFile("cachefile1");
	cur->setCacheTtl(200);
	checkSuccess(cur->sendQuery("select * from testtable order by testnumber"),1);
	filename=strdup(cur->getCacheFileName());
	checkSuccess(filename,"cachefile1");
	cur->cacheOff();
	checkSuccess(cur->openCachedResultSet(filename),1);
	checkSuccess(cur->getField(7,(uint32_t)0),"8");
	delete[] filename;
	printf("\n");

	printf("COLUMN COUNT FOR CACHED RESULT SET: \n");
	checkSuccess(cur->colCount(),5);
	printf("\n");

	printf("COLUMN NAMES FOR CACHED RESULT SET: \n");
	checkSuccess(cur->getColumnName(0),"TESTNUMBER");
	checkSuccess(cur->getColumnName(1),"TESTCHAR");
	checkSuccess(cur->getColumnName(2),"TESTVARCHAR");
	checkSuccess(cur->getColumnName(3),"TESTDATE");
	checkSuccess(cur->getColumnName(4),"TESTLONG");
	cols=cur->getColumnNames();
	checkSuccess(cols[0],"TESTNUMBER");
	checkSuccess(cols[1],"TESTCHAR");
	checkSuccess(cols[2],"TESTVARCHAR");
	checkSuccess(cols[3],"TESTDATE");
	checkSuccess(cols[4],"TESTLONG");
	printf("\n");

	printf("CACHED RESULT SET WITH RESULT SET BUFFER SIZE: \n");
	cur->setResultSetBufferSize(2);
	cur->cacheToFile("cachefile1");
	cur->setCacheTtl(200);
	checkSuccess(cur->sendQuery("select * from testtable order by testnumber"),1);
	filename=strdup(cur->getCacheFileName());
	checkSuccess(filename,"cachefile1");
	cur->cacheOff();
	checkSuccess(cur->openCachedResultSet(filename),1);
	checkSuccess(cur->getField(7,(uint32_t)0),"8");
	checkSuccess(cur->getField(8,(uint32_t)0),NULL);
	cur->setResultSetBufferSize(0);
	delete[] filename;
	printf("\n");

	printf("FROM ONE CACHE FILE TO ANOTHER: \n");
	cur->cacheToFile("cachefile2");
	checkSuccess(cur->openCachedResultSet("cachefile1"),1);
	cur->cacheOff();
	checkSuccess(cur->openCachedResultSet("cachefile2"),1);
	checkSuccess(cur->getField(7,(uint32_t)0),"8");
	checkSuccess(cur->getField(8,(uint32_t)0),NULL);
	printf("\n");

	printf("FROM ONE CACHE FILE TO ANOTHER WITH RESULT SET BUFFER SIZE: \n");
	cur->setResultSetBufferSize(2);
	cur->cacheToFile("cachefile2");
	checkSuccess(cur->openCachedResultSet("cachefile1"),1);
	cur->cacheOff();
	checkSuccess(cur->openCachedResultSet("cachefile2"),1);
	checkSuccess(cur->getField(7,(uint32_t)0),"8");
	checkSuccess(cur->getField(8,(uint32_t)0),NULL);
	cur->setResultSetBufferSize(0);
	printf("\n");

	printf("CACHED RESULT SET WITH SUSPEND AND RESULT SET BUFFER SIZE: \n");
	cur->setResultSetBufferSize(2);
	cur->cacheToFile("cachefile1");
	cur->setCacheTtl(200);
	checkSuccess(cur->sendQuery("select * from testtable order by testnumber"),1);
	checkSuccess(cur->getField(2,(uint32_t)0),"3");
	filename=strdup(cur->getCacheFileName());
	checkSuccess(filename,"cachefile1");
	id=cur->getResultSetId();
	cur->suspendResultSet();
	checkSuccess(con->suspendSession(),1);
	port=con->getConnectionPort();
	socket=strdup(con->getConnectionSocket());
	printf("\n");
	checkSuccess(con->resumeSession(port,socket),1);
	checkSuccess(cur->resumeCachedResultSet(id,filename),1);
	printf("\n");
	checkSuccess(cur->firstRowIndex(),4);
	checkSuccess(cur->endOfResultSet(),0);
	checkSuccess(cur->rowCount(),6);
	checkSuccess(cur->getField(7,(uint32_t)0),"8");
	printf("\n");
	checkSuccess(cur->firstRowIndex(),6);
	checkSuccess(cur->endOfResultSet(),0);
	checkSuccess(cur->rowCount(),8);
	checkSuccess(cur->getField(8,(uint32_t)0),NULL);
	printf("\n");
	checkSuccess(cur->firstRowIndex(),8);
	checkSuccess(cur->endOfResultSet(),1);
	checkSuccess(cur->rowCount(),8);
	cur->cacheOff();
	printf("\n");
	checkSuccess(cur->openCachedResultSet(filename),1);
	checkSuccess(cur->getField(7,(uint32_t)0),"8");
	checkSuccess(cur->getField(8,(uint32_t)0),NULL);
	cur->setResultSetBufferSize(0);
	delete[] filename;
	printf("\n");

	printf("FINISHED SUSPENDED SESSION: \n");
	checkSuccess(cur->sendQuery("select * from testtable order by testnumber"),1);
	checkSuccess(cur->getField(4,(uint32_t)0),"5");
	checkSuccess(cur->getField(5,(uint32_t)0),"6");
	checkSuccess(cur->getField(6,(uint32_t)0),"7");
	checkSuccess(cur->getField(7,(uint32_t)0),"8");
	id=cur->getResultSetId();
	cur->suspendResultSet();
	checkSuccess(con->suspendSession(),1);
	port=con->getConnectionPort();
	socket=strdup(con->getConnectionSocket());
	checkSuccess(con->resumeSession(port,socket),1);
	checkSuccess(cur->resumeResultSet(id),1);
	checkSuccess(cur->getField(4,(uint32_t)0),NULL);
	checkSuccess(cur->getField(5,(uint32_t)0),NULL);
	checkSuccess(cur->getField(6,(uint32_t)0),NULL);
	checkSuccess(cur->getField(7,(uint32_t)0),NULL);
	printf("\n");

	printf("LONG OUTPUT BIND\n");
	cur->sendQuery("drop table testtable2");
	cur->sendQuery("create table testtable2 (testval varchar2(2000))");
	char	testval[2001];
	testval[2000]='\0';
	cur->prepareQuery("insert into testtable2 values (:testval)");
	for (int i=0; i<2000; i++) {
		testval[i]='C';
	}
	cur->inputBind("testval",testval);
	checkSuccess(cur->executeQuery(),1);
	cur->sendQuery("select testval from testtable2");
	checkSuccess(testval,cur->getField(0,"testval"));
	char	query[2000+25];
	sprintf(query,"begin :bindval:='%s'; end;",testval);
	cur->prepareQuery(query);
	cur->defineOutputBindString("bindval",2000);
	checkSuccess(cur->executeQuery(),1);
	checkSuccess(cur->getOutputBindLength("bindval"),2000);
	checkSuccess(cur->getOutputBindString("bindval"),testval);
	cur->sendQuery("drop table testtable2");
	printf("\n");

	printf("NEGATIVE INPUT BIND\n");
	cur->sendQuery("drop table testtable2");
	cur->sendQuery("create table testtable2 (testval number)");
	cur->prepareQuery("insert into testtable2 values (:testval)");
	cur->inputBind("testval",-1);
	checkSuccess(cur->executeQuery(),1);
	cur->sendQuery("select testval from testtable2");
	checkSuccess(cur->getField(0,"testval"),"-1");
	cur->sendQuery("drop table testtable2");
	printf("\n");



	printf("BIND VALIDATION: \n");
	cur->sendQuery("drop table testtable1");
	cur->sendQuery("create table testtable1 (col1 varchar2(20), col2 varchar2(20), col3 varchar2(20))");
	cur->prepareQuery("insert into testtable1 values ($(var1),$(var2),$(var3))");
	cur->inputBind("var1",1);
	cur->inputBind("var2",2);
	cur->inputBind("var3",3);
	cur->substitution("var1",":var1");
	checkSuccess(cur->validBind("var1"),1);
	checkSuccess(cur->validBind("var2"),0);
	checkSuccess(cur->validBind("var3"),0);
	checkSuccess(cur->validBind("var4"),0);
	printf("\n");
	cur->substitution("var2",":var2");
	checkSuccess(cur->validBind("var1"),1);
	checkSuccess(cur->validBind("var2"),1);
	checkSuccess(cur->validBind("var3"),0);
	checkSuccess(cur->validBind("var4"),0);
	printf("\n");
	cur->substitution("var3",":var3");
	checkSuccess(cur->validBind("var1"),1);
	checkSuccess(cur->validBind("var2"),1);
	checkSuccess(cur->validBind("var3"),1);
	checkSuccess(cur->validBind("var4"),0);
	checkSuccess(cur->executeQuery(),1);
	cur->sendQuery("drop table testtable1");
	printf("\n");

	// drop existing table
	cur->sendQuery("drop table testtable");


	// stored procedures
	printf("STORED PROCEDURE: \n");
	// return no value
	cur->sendQuery("drop function testproc");
	cur->sendQuery("drop procedure testproc");
	checkSuccess(cur->sendQuery("create or replace procedure testproc(in1 in number, in2 in number, in3 in varchar2) is begin return; end;"),1);
	cur->prepareQuery("begin testproc(:in1,:in2,:in3); end;");
	cur->inputBind("in1",1);
	cur->inputBind("in2",1.1,2,1);
	cur->inputBind("in3","hello");
	checkSuccess(cur->executeQuery(),1);
	// return single value
	cur->sendQuery("drop function testproc");
	cur->sendQuery("drop procedure testproc");
	checkSuccess(cur->sendQuery("create or replace function testproc(in1 in number, in2 in number, in3 in varchar2) return number is begin return in1; end;"),1);
	cur->prepareQuery("select testproc(:in1,:in2,:in3) from dual");
	cur->inputBind("in1",1);
	cur->inputBind("in2",1.1,2,1);
	cur->inputBind("in3","hello");
	checkSuccess(cur->executeQuery(),1);
	checkSuccess(cur->getField(0,(uint32_t)0),"1");
	cur->prepareQuery("begin  :out1:=testproc(:in1,:in2,:in3); end;");
	cur->inputBind("in1",1);
	cur->inputBind("in2",1.1,2,1);
	cur->inputBind("in3","hello");
	cur->defineOutputBindInteger("out1");
	checkSuccess(cur->executeQuery(),1);
	checkSuccess(cur->getOutputBindInteger("out1"),1);
	// return multiple values
	cur->sendQuery("drop function testproc");
	cur->sendQuery("drop procedure testproc");
	checkSuccess(cur->sendQuery("create or replace procedure testproc(in1 in number, in2 in number, in3 in varchar2, out1 out number, out2 out number, out3 out varchar2) is begin out1:=in1; out2:=in2; out3:=in3; end;"),1);
	cur->prepareQuery("begin testproc(:in1,:in2,:in3,:out1,:out2,:out3); end;");
	cur->inputBind("in1",1);
	cur->inputBind("in2",1.1,2,1);
	cur->inputBind("in3","hello");
	cur->defineOutputBindInteger("out1");
	cur->defineOutputBindDouble("out2");
	cur->defineOutputBindString("out3",20);
	checkSuccess(cur->executeQuery(),1);
	checkSuccess(cur->getOutputBindInteger("out1"),1);
	checkSuccess(cur->getOutputBindDouble("out2"),1.1);
	checkSuccess(cur->getOutputBindString("out3"),"hello");
	cur->sendQuery("drop function testproc");
	cur->sendQuery("drop procedure testproc");
	printf("\n");


	// in/out variables
	/*printf("IN/OUT VARIABLES: \n");
	cur->sendQuery("drop procedure testproc");
	checkSuccess(cur->sendQuery("create or replace procedure testproc(inout in out number) is begin inout:=inout+1; return; end;"),1);
	cur->prepareQuery("begin testproc(:inout); end;");
	cur->inputBind("inout",1);
	cur->defineOutputBindInteger("inout");
	checkSuccess(cur->executeQuery(),1);
	checkSuccess(cur->getOutputBindInteger("inout"),2);
	cur->sendQuery("drop procedure testproc");
	printf("\n");*/



	// rebinding
	printf("REBINDING: \n");
	cur->sendQuery("drop procedure testproc");
	checkSuccess(cur->sendQuery("create or replace procedure testproc(in1 in number, out1 out number) is begin out1:=in1; return; end;"),1);
	cur->prepareQuery("begin testproc(:in,:out); end;");
	cur->inputBind("in",1);
	cur->defineOutputBindInteger("out");
	checkSuccess(cur->executeQuery(),1);
	checkSuccess(cur->getOutputBindInteger("out"),1);
	cur->inputBind("in",2);
	checkSuccess(cur->executeQuery(),1);
	checkSuccess(cur->getOutputBindInteger("out"),2);
	cur->inputBind("in",3);
	checkSuccess(cur->executeQuery(),1);
	checkSuccess(cur->getOutputBindInteger("out"),3);
	cur->sendQuery("drop procedure testproc");
	printf("\n");


	// invalid queries...
	printf("INVALID QUERIES: \n");
	checkSuccess(cur->sendQuery("select * from testtable order by testnumber"),0);
	checkSuccess(cur->sendQuery("select * from testtable order by testnumber"),0);
	checkSuccess(cur->sendQuery("select * from testtable order by testnumber"),0);
	checkSuccess(cur->sendQuery("select * from testtable order by testnumber"),0);
	printf("\n");
	checkSuccess(cur->sendQuery("insert into testtable values (1,2,3,4)"),0);
	checkSuccess(cur->sendQuery("insert into testtable values (1,2,3,4)"),0);
	checkSuccess(cur->sendQuery("insert into testtable values (1,2,3,4)"),0);
	checkSuccess(cur->sendQuery("insert into testtable values (1,2,3,4)"),0);
	printf("\n");
	checkSuccess(cur->sendQuery("create table testtable"),0);
	checkSuccess(cur->sendQuery("create table testtable"),0);
	checkSuccess(cur->sendQuery("create table testtable"),0);
	checkSuccess(cur->sendQuery("create table testtable"),0);
	printf("\n");


	delete cur;
	delete con;

}
