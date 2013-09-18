// Copyright (c) 1999-2001  David Muse
// See the file COPYING for more information

#include <config.h>
#include <sqlrelay/sqlrclient.h>
#include <rudiments/rawbuffer.h>
#include <rudiments/character.h>
#include <defines.h>

uint16_t sqlrcursor::countBindVariables() const {

	if (!queryptr) {
		return 0;
	}

	char	lastchar='\0';
	bool	inquotes=false;

	uint16_t	questionmarkcount=0;
	uint16_t	coloncount=0;
	uint16_t	atsigncount=0;
	uint16_t	dollarsigncount=0;

	for (const char *ptr=queryptr; *ptr; ptr++) {

		if (*ptr=='\'' && lastchar!='\\') {
			if (inquotes) {
				inquotes=false;
			} else {
				inquotes=true;
			}
		}

		// If we're not inside of a quoted string and we run into
		// a ?, : (for oracle-style bind's), @ (for sybase-style
		// binds) or $ (for postgresql-style binds) and the previous
		// character was something that might come before a bind
		// variable then we must have found a bind variable.
		// count ?, :, @, $ separately
		if (!inquotes &&
			character::inSet(lastchar," \t\n\r=<>,(+-*/%|&!~^")) {
			if (*ptr=='?') {
				questionmarkcount++;
			} else if (*ptr==':') {
				coloncount++;
			} else if (*ptr=='@') {
				atsigncount++;
			} else if (*ptr=='$') {
				dollarsigncount++;
			}
		}

		lastchar=*ptr;
	}

	// if we got $'s or ?'s, ignore the :'s or @'s
	if (dollarsigncount) {
		return dollarsigncount;
	}
	if (questionmarkcount) {
		return questionmarkcount;
	}
	if (coloncount) {
		return coloncount;
	}
	if (atsigncount) {
		return atsigncount;
	}
	return 0;
}

void sqlrcursor::clearVariables() {

	// setting the bind/substitution variable 
	// counts to 0 effectively clears them
	subcount=0;
	dirtysubs=false;
	dirtybinds=false;
	clearBinds();
}

void sqlrcursor::initVariables() {

	// initialize the bind and substitution variables
	for (int16_t i=0; i<MAXVAR; i++) {
		subvars[i].variable=NULL;
		subvars[i].value.stringval=NULL;
		subvars[i].type=STRING_BIND;
		subvars[i].substituted=false;
		subvars[i].donesubstituting=false;
		inbindvars[i].variable=NULL;
		inbindvars[i].value.stringval=NULL;
		inbindvars[i].type=STRING_BIND;
		outbindvars[i].variable=NULL;
		outbindvars[i].value.stringval=NULL;
		outbindvars[i].type=STRING_BIND;
	}
}

void sqlrcursor::deleteVariables() {

	// if we were copying values, delete them
	if (copyrefs) {
		for (int16_t i=0; i<MAXVAR; i++) {
			delete[] inbindvars[i].variable;
			if (inbindvars[i].type==STRING_BIND) {
				delete[] inbindvars[i].value.stringval;
			}
			if (inbindvars[i].type==BLOB_BIND ||
				inbindvars[i].type==CLOB_BIND) {
				delete[] inbindvars[i].value.lobval;
			}
			delete[] outbindvars[i].variable;
			delete[] subvars[i].variable;
			if (subvars[i].type==STRING_BIND) {
				delete[] subvars[i].value.stringval;
			}
			if (subvars[i].type==DATE_BIND) {
				delete[] subvars[i].value.dateval.tz;
			}
		}
	}

	// output binds are deleted no matter what
	for (int16_t i=0; i<MAXVAR; i++) {
		if (outbindvars[i].type==STRING_BIND) {
			delete[] outbindvars[i].value.stringval;
		}
		if (outbindvars[i].type==BLOB_BIND ||
			outbindvars[i].type==CLOB_BIND) {
			delete[] outbindvars[i].value.lobval;
		}
	}
}

void sqlrcursor::substitution(const char *variable, const char *value) {
	if (!variable || !variable[0]) {
		return;
	}
	bindvar	*bv=findVar(variable,subvars,subcount);
	if (!bv) {
		if (subcount>=MAXVAR) {
			return;
		}
		bv=&subvars[subcount];
		subcount++;
	}
	stringVar(bv,variable,value);
	dirtysubs=true;
}

void sqlrcursor::substitution(const char *variable, int64_t value) {
	if (!variable || !variable[0]) {
		return;
	}
	bindvar	*bv=findVar(variable,subvars,subcount);
	if (!bv) {
		if (subcount>=MAXVAR) {
			return;
		}
		bv=&subvars[subcount];
		subcount++;
	}
	integerVar(bv,variable,value);
	dirtysubs=true;
}

void sqlrcursor::substitution(const char *variable, double value, 
				uint32_t precision, uint32_t scale) {
	if (!variable || !variable[0]) {
		return;
	}
	bindvar	*bv=findVar(variable,subvars,subcount);
	if (!bv) {
		if (subcount>=MAXVAR) {
			return;
		}
		bv=&subvars[subcount];
		subcount++;
	}
	doubleVar(bv,variable,value,precision,scale);
	dirtysubs=true;
}

void sqlrcursor::clearBinds() {
	inbindcount=0;
	outbindcount=0;
}

void sqlrcursor::inputBindBlob(const char *variable, const char *value,
							uint32_t size) {
	if (!variable || !variable[0]) {
		return;
	}
	bindvar	*bv=findVar(variable,inbindvars,inbindcount);
	if (!bv) {
		if (inbindcount>=MAXVAR) {
			return;
		}
		bv=&inbindvars[inbindcount];
		inbindcount++;
	}
	lobVar(bv,variable,value,size,BLOB_BIND);
	bv->send=true;
	dirtybinds=true;
}

void sqlrcursor::inputBindClob(const char *variable, const char *value,
							uint32_t size) {
	if (!variable || !variable[0]) {
		return;
	}
	bindvar	*bv=findVar(variable,inbindvars,inbindcount);
	if (!bv) {
		if (inbindcount>=MAXVAR) {
			return;
		}
		bv=&inbindvars[inbindcount];
		inbindcount++;
	}
	lobVar(bv,variable,value,size,CLOB_BIND);
	bv->send=true;
	dirtybinds=true;
}

void sqlrcursor::inputBind(const char *variable, const char *value) {
	if (!variable || !variable[0]) {
		return;
	}
	bindvar	*bv=findVar(variable,inbindvars,inbindcount);
	if (!bv) {
		if (inbindcount>=MAXVAR) {
			return;
		}
		bv=&inbindvars[inbindcount];
		inbindcount++;
	}
	stringVar(bv,variable,value);
	bv->send=true;
	dirtybinds=true;
}

void sqlrcursor::inputBind(const char *variable, const char *value,
						uint32_t valuesize) {
	if (!variable || !variable[0]) {
		return;
	}
	bindvar	*bv=findVar(variable,inbindvars,inbindcount);
	if (!bv) {
		if (inbindcount>=MAXVAR) {
			return;
		}
		bv=&inbindvars[inbindcount];
		inbindcount++;
	}
	stringVar(bv,variable,value,valuesize);
	bv->send=true;
	dirtybinds=true;
}

void sqlrcursor::inputBind(const char *variable, int64_t value) {
	if (!variable || !variable[0]) {
		return;
	}
	bindvar	*bv=findVar(variable,inbindvars,inbindcount);
	if (!bv) {
		if (inbindcount>=MAXVAR) {
			return;
		}
		bv=&inbindvars[inbindcount];
		inbindcount++;
	}
	integerVar(bv,variable,value);
	bv->send=true;
	dirtybinds=true;
}

void sqlrcursor::inputBind(const char *variable, double value, 
				uint32_t precision, uint32_t scale) {
	if (!variable || !variable[0]) {
		return;
	}
	bindvar	*bv=findVar(variable,inbindvars,inbindcount);
	if (!bv) {
		if (inbindcount>=MAXVAR) {
			return;
		}
		bv=&inbindvars[inbindcount];
		inbindcount++;
	}
	doubleVar(bv,variable,value,precision,scale);
	bv->send=true;
	dirtybinds=true;
}

void sqlrcursor::inputBind(const char *variable,
				int16_t year, int16_t month, int16_t day,
				int16_t hour, int16_t minute, int16_t second,
				int32_t microsecond, const char *tz) {
	if (!variable || !variable[0]) {
		return;
	}
	bindvar	*bv=findVar(variable,inbindvars,inbindcount);
	if (!bv) {
		if (inbindcount>=MAXVAR) {
			return;
		}
		bv=&inbindvars[inbindcount];
		inbindcount++;
	}
	dateVar(bv,variable,year,month,day,hour,minute,second,microsecond,tz);
	bv->send=true;
	dirtybinds=true;
}

void sqlrcursor::substitutions(const char **variables, const char **values) {
	for (uint16_t i=0; variables[i]; i++) {
		substitution(variables[i],values[i]);
	}
}

void sqlrcursor::substitutions(const char **variables, const int64_t *values) {
	for (uint16_t i=0; variables[i]; i++) {
		substitution(variables[i],values[i]);
	}
}

void sqlrcursor::substitutions(const char **variables, const double *values, 
					const uint32_t *precisions,
					const uint32_t *scales) {
	for (uint16_t i=0; variables[i]; i++) {
		substitution(variables[i],values[i],precisions[i],scales[i]);
	}
}

void sqlrcursor::inputBinds(const char **variables, const char **values) {
	for (uint16_t i=0; variables[i]; i++) {
		inputBind(variables[i],values[i]);
	}
}

void sqlrcursor::inputBinds(const char **variables, const int64_t *values) {
	for (uint16_t i=0; variables[i]; i++) {
		inputBind(variables[i],values[i]);
	}
}

void sqlrcursor::inputBinds(const char **variables, const double *values, 
					const uint32_t *precisions,
					const uint32_t *scales) {
	for (uint16_t i=0; variables[i]; i++) {
		inputBind(variables[i],values[i],
				precisions[i],scales[i]);
	}
}

void sqlrcursor::stringVar(bindvar *var, const char *variable,
	stringVar(var,variable,value,charstring::length(value));
}

void sqlrcursor::stringVar(bindvar *var, const char *variable,
						const char *value,
						uint32_t valuesize) {

	initVar(var,variable);

	// store the value, handle NULL values too
	if (value) {
		if (copyrefs) {
			var->value.stringval=charstring::duplicate(value);
		} else {
			var->value.stringval=(char *)value;
		}
		var->valuesize=valuesize;
		var->type=STRING_BIND;
	} else {
		var->type=NULL_BIND;
	}
}

void sqlrcursor::integerVar(bindvar *var, const char *variable, int64_t value) {
	initVar(var,variable);
	var->type=INTEGER_BIND;
	var->value.integerval=value;
}

void sqlrcursor::doubleVar(bindvar *var, const char *variable, double value,
					uint32_t precision, uint32_t scale) {
	initVar(var,variable);
	var->type=DOUBLE_BIND;
	var->value.doubleval.value=value;
	var->value.doubleval.precision=precision;
	var->value.doubleval.scale=scale;
}

void sqlrcursor::dateVar(bindvar *var, const char *variable,
				int16_t year, int16_t month, int16_t day,
				int16_t hour, int16_t minute, int16_t second,
				int32_t microsecond, const char *tz) {
	initVar(var,variable);
	var->type=DATE_BIND;
	var->value.dateval.year=year;
	var->value.dateval.month=month;
	var->value.dateval.day=day;
	var->value.dateval.hour=hour;
	var->value.dateval.minute=minute;
	var->value.dateval.second=second;
	var->value.dateval.microsecond=microsecond;
	if (copyrefs) {
		var->value.dateval.tz=charstring::duplicate(tz);
	} else {
		var->value.dateval.tz=(char *)tz;
	}
}

void sqlrcursor::lobVar(bindvar *var, const char *variable,
			const char *value, uint32_t size, uint16_t type) {

	initVar(var,variable);

	// Store the value, handle NULL values too.
	// For LOB's empty strings are handled as NULL's as well, this is
	// probably not right, but I can't get empty string lob binds to work.
	if (value && size>0) {
		if (copyrefs) {
			var->value.lobval=new char[size];
			rawbuffer::copy(var->value.lobval,value,size);
		} else {
			var->value.lobval=(char *)value;
		}
		var->valuesize=size;
		var->type=type;
	} else {
		var->type=NULL_BIND;
	}
}

bindvar *sqlrcursor::findVar(const char *variable,
				bindvar *vars, uint16_t count) {
	for (uint16_t i=0; i<count; i++) {
		if (!charstring::compare(vars[i].variable,variable)) {
			return &(vars[i]);
		}
	}
	return NULL;
}

void sqlrcursor::initVar(bindvar *var, const char *variable) {

	// clear any old variable name that was stored and assign the new 
	// variable name also clear any old value that was stored in this 
	// variable
	if (copyrefs) {
		delete[] var->variable;
		var->variable=charstring::duplicate(variable);

		if (var->type==STRING_BIND &&
				var->value.stringval) {
			delete[] var->value.stringval;
		} else if ((var->type==BLOB_BIND ||
				var->type==CLOB_BIND) &&
				var->value.lobval) {
			delete[] var->value.lobval;
		}
	} else {
		var->variable=(char *)variable;
	}

	var->substituted=false;
	var->donesubstituting=false;
}

void sqlrcursor::defineOutputBindString(const char *variable,
						uint32_t length) {
	defineOutputBindGeneric(variable,STRING_BIND,length);
}

void sqlrcursor::defineOutputBindInteger(const char *variable) {
	defineOutputBindGeneric(variable,INTEGER_BIND,sizeof(int64_t));
}

void sqlrcursor::defineOutputBindDouble(const char *variable) {
	defineOutputBindGeneric(variable,DOUBLE_BIND,sizeof(double));
}

void sqlrcursor::defineOutputBindDate(const char *variable) {
	defineOutputBindGeneric(variable,DATE_BIND,sizeof(double));
}

void sqlrcursor::defineOutputBindBlob(const char *variable) {
	defineOutputBindGeneric(variable,BLOB_BIND,0);
}

void sqlrcursor::defineOutputBindClob(const char *variable) {
	defineOutputBindGeneric(variable,CLOB_BIND,0);
}

void sqlrcursor::defineOutputBindCursor(const char *variable) {
	defineOutputBindGeneric(variable,CURSOR_BIND,0);
}

void sqlrcursor::defineOutputBindGeneric(const char *variable,
				uint16_t type, uint32_t valuesize) {

	if (!variable || !variable[0]) {
		return;
	}

	bindvar	*bv=findVar(variable,outbindvars,outbindcount);
	if (!bv) {
		if (outbindcount>=MAXVAR) {
			return;
		}
		bv=&outbindvars[outbindcount];
		dirtybinds=true;
		outbindcount++;
	}

	// clean up old values
	if (bv->type==STRING_BIND) {
		delete[] bv->value.stringval;
		bv->value.stringval=NULL;
	} else if (bv->type==BLOB_BIND || bv->type==CLOB_BIND) {
		delete[] bv->value.lobval;
		bv->value.lobval=NULL;
	}
	if (copyrefs) {
		// clean up old variable and set new variable
		delete[] bv->variable;
		bv->variable=charstring::duplicate(variable);
	} else {
		bv->variable=(char *)variable;
	}
	bv->type=type;
	bv->valuesize=valuesize;
	bv->resultvaluesize=0;
	bv->send=true;
}

const char *sqlrcursor::getOutputBindString(const char *variable) {

	if (variable) {
		for (int16_t i=0; i<outbindcount; i++) {
			if (!charstring::compare(
					outbindvars[i].variable,variable) &&
					outbindvars[i].type==STRING_BIND) {
				return outbindvars[i].value.stringval;
			}
		}
	}
	return NULL;
}

uint32_t sqlrcursor::getOutputBindLength(const char *variable) {

	if (variable) {
		for (int16_t i=0; i<outbindcount; i++) {
			if (!charstring::compare(outbindvars[i].variable,
								variable)) {
				return outbindvars[i].resultvaluesize;
			}
		}
	}
	return 0;
}

const char *sqlrcursor::getOutputBindBlob(const char *variable) {

	if (variable) {
		for (int16_t i=0; i<outbindcount; i++) {
			if (!charstring::compare(
					outbindvars[i].variable,variable) &&
					outbindvars[i].type==BLOB_BIND) {
				return outbindvars[i].value.lobval;
			}
		}
	}
	return NULL;
}

const char *sqlrcursor::getOutputBindClob(const char *variable) {

	if (variable) {
		for (int16_t i=0; i<outbindcount; i++) {
			if (!charstring::compare(
					outbindvars[i].variable,variable) &&
					outbindvars[i].type==CLOB_BIND) {
				return outbindvars[i].value.lobval;
			}
		}
	}
	return NULL;
}

int64_t sqlrcursor::getOutputBindInteger(const char *variable) {

	if (variable) {
		for (int16_t i=0; i<outbindcount; i++) {
			if (!charstring::compare(
					outbindvars[i].variable,variable) &&
					outbindvars[i].type==INTEGER_BIND) {
				return outbindvars[i].value.integerval;
			}
		}
	}
	return -1;
}

double sqlrcursor::getOutputBindDouble(const char *variable) {

	if (variable) {
		for (int16_t i=0; i<outbindcount; i++) {
			if (!charstring::compare(
					outbindvars[i].variable,variable) &&
					outbindvars[i].type==DOUBLE_BIND) {
				return outbindvars[i].value.doubleval.value;
			}
		}
	}
	return -1.0;
}

bool sqlrcursor::getOutputBindDate(const char *variable,
			int16_t *year, int16_t *month, int16_t *day,
			int16_t *hour, int16_t *minute, int16_t *second,
			int32_t *microsecond, const char **tz) {

	if (variable) {
		for (int16_t i=0; i<outbindcount; i++) {
			if (!charstring::compare(
					outbindvars[i].variable,variable) &&
					outbindvars[i].type==DATE_BIND) {
				*year=outbindvars[i].value.dateval.year;
				*month=outbindvars[i].value.dateval.month;
				*day=outbindvars[i].value.dateval.day;
				*hour=outbindvars[i].value.dateval.hour;
				*minute=outbindvars[i].value.dateval.minute;
				*second=outbindvars[i].value.dateval.second;
				*microsecond=outbindvars[i].
						value.dateval.microsecond;
				*tz=outbindvars[i].value.dateval.tz;
				return true;
			}
		}
	}
	return false;
}

sqlrcursor *sqlrcursor::getOutputBindCursor(const char *variable) {
	return getOutputBindCursor(variable,false);
}

sqlrcursor *sqlrcursor::getOutputBindCursor(const char *variable,
							bool copyrefs) {

	if (!outputBindCursorIdIsValid(variable)) {
		return NULL;
	}
	uint16_t	bindcursorid=getOutputBindCursorId(variable);
	sqlrcursor	*bindcursor=new sqlrcursor(sqlrc,copyrefs);
	bindcursor->attachToBindCursor(bindcursorid);
	return bindcursor;
}

bool sqlrcursor::outputBindCursorIdIsValid(const char *variable) {
	if (variable) {
		for (int16_t i=0; i<outbindcount; i++) {
			if (!charstring::compare(outbindvars[i].variable,
								variable)) {
				return true;
			}
		}
	}
	return false;
}

uint16_t sqlrcursor::getOutputBindCursorId(const char *variable) {

	if (variable) {
		for (int16_t i=0; i<outbindcount; i++) {
			if (!charstring::compare(outbindvars[i].variable,
								variable)) {
				return outbindvars[i].value.cursorid;
			}
		}
	}
	return 0;
}

void sqlrcursor::validateBinds() {
	validatebinds=true;
}

bool sqlrcursor::validBind(const char *variable) {
	performSubstitutions();
	validateBindsInternal();
	for (uint16_t i=0; i<inbindcount; i++) {
		if (!charstring::compare(inbindvars[i].variable,variable)) {
			return inbindvars[i].send;
		}
	}
	for (uint16_t i=0; i<outbindcount; i++) {
		if (!charstring::compare(outbindvars[i].variable,variable)) {
			return outbindvars[i].send;
		}
	}
	return false;
}
