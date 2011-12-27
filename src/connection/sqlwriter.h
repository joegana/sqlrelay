// Copyright (c) 1999-2011  David Muse
// See the file COPYING for more information

#ifndef SQLWRITER_H
#define SQLWRITER_H

#include <rudiments/xmldom.h>
#include <rudiments/xmldomnode.h>

using namespace rudiments;

class sqlrconnection_svr;
class sqlrcursor_svr;

class sqlwriter {
	public:
			sqlwriter();
		virtual	~sqlwriter();

		virtual bool	write(sqlrconnection_svr *sqlrcon,
					sqlrcursor_svr *sqlrcur,
					xmldom *tree,
					stringbuffer *output);
		virtual bool	write(sqlrconnection_svr *sqlrcon,
					sqlrcursor_svr *sqlrcur,
					xmldomnode *tree,
					stringbuffer *output);
	protected:
		virtual bool	write(xmldomnode *tree, stringbuffer *output);

		virtual const char * const *baseElements();
		virtual const char * const *additionalElements();
		virtual const char * const *unsupportedElements();

		virtual	bool	elementSupported(const char *element);
		virtual bool	handleStart(xmldomnode *node,
						stringbuffer *output);
		virtual bool	handleEnd(xmldomnode *node,
						stringbuffer *output);

		// generic
		virtual bool	name(xmldomnode *node,
						stringbuffer *output);
		virtual bool	type(xmldomnode *node,
						stringbuffer *output);
		virtual bool	endType(xmldomnode *node,
						stringbuffer *output);
		virtual bool	size(xmldomnode *node,
						stringbuffer *output);
		virtual bool	endSize(xmldomnode *node,
						stringbuffer *output);
		virtual bool	value(xmldomnode *node,
						stringbuffer *output);
		virtual bool	verbatim(xmldomnode *node,
						stringbuffer *output);

		// create query...
		virtual bool	createQuery(xmldomnode *node,
						stringbuffer *output);

		// table...
		virtual bool	table(xmldomnode *node,
						stringbuffer *output);
		virtual bool	temporary(xmldomnode *node,
						stringbuffer *output);
		virtual bool	ifNotExists(xmldomnode *node,
						stringbuffer *output);

		// column definitions...
		virtual bool	columns(xmldomnode *node,
						stringbuffer *output);
		virtual bool	endColumns(xmldomnode *node,
						stringbuffer *output);
		virtual bool	column(xmldomnode *node,
						stringbuffer *output);
		virtual bool	endColumn(xmldomnode *node,
						stringbuffer *output);
		virtual bool	values(xmldomnode *node,
						stringbuffer *output);
		virtual bool	endValues(xmldomnode *node,
						stringbuffer *output);
		virtual bool	length(xmldomnode *node,
						stringbuffer *output);
		virtual bool	scale(xmldomnode *node,
						stringbuffer *output);

		// constraints...
		virtual bool	constraints(xmldomnode *node,
						stringbuffer *output);
		virtual bool	unsignedConstraint(xmldomnode *node,
						stringbuffer *output);
		virtual bool	zerofill(xmldomnode *node,
						stringbuffer *output);
		virtual bool	binary(xmldomnode *node,
						stringbuffer *output);
		virtual bool	characterSet(xmldomnode *node,
						stringbuffer *output);
		virtual bool	collate(xmldomnode *node,
						stringbuffer *output);
		virtual bool	nullable(xmldomnode *node,
						stringbuffer *output);
		virtual bool	notNull(xmldomnode *node,
						stringbuffer *output);
		virtual bool	defaultValue(xmldomnode *node,
						stringbuffer *output);
		virtual bool	autoIncrement(xmldomnode *node,
						stringbuffer *output);
		virtual bool	uniqueKey(xmldomnode *node,
						stringbuffer *output);
		virtual bool	primaryKey(xmldomnode *node,
						stringbuffer *output);
		virtual bool	key(xmldomnode *node,
						stringbuffer *output);
		virtual bool	comment(xmldomnode *node,
						stringbuffer *output);
		virtual bool	columnFormat(xmldomnode *node,
						stringbuffer *output);
		virtual bool	references(xmldomnode *node,
						stringbuffer *output);
		virtual bool	endReferences(xmldomnode *node,
						stringbuffer *output);
		virtual bool	match(xmldomnode *node,
						stringbuffer *output);
		virtual bool	onDelete(xmldomnode *node,
						stringbuffer *output);
		virtual bool	onUpdate(xmldomnode *node,
						stringbuffer *output);
		virtual bool	onCommit(xmldomnode *node,
						stringbuffer *output);
		virtual bool	as(xmldomnode *node,
						stringbuffer *output);


		// drop...
		virtual bool	dropQuery(xmldomnode *node,
						stringbuffer *output);
		virtual bool	ifExists(xmldomnode *node,
						stringbuffer *output);
		virtual bool	endTableNameListItem(xmldomnode *node,
						stringbuffer *output);
		virtual bool	restrictClause(xmldomnode *node,
						stringbuffer *output);
		virtual bool	cascade(xmldomnode *node,
						stringbuffer *output);


		// insert...
		virtual bool	insertQuery(xmldomnode *node,
						stringbuffer *output);
		virtual bool	insertInto(xmldomnode *node,
						stringbuffer *output);
		virtual bool	insertValues(xmldomnode *node,
						stringbuffer *output);
		virtual bool	endInsertValues(xmldomnode *node,
						stringbuffer *output);
		virtual bool	insertValue(xmldomnode *node,
						stringbuffer *output);
		virtual bool	endInsertValue(xmldomnode *node,
						stringbuffer *output);


		// update...
		virtual bool	updateQuery(xmldomnode *node,
						stringbuffer *output);
		virtual bool	updateSet(xmldomnode *node,
						stringbuffer *output);
		virtual bool	assignment(xmldomnode *node,
						stringbuffer *output);
		virtual bool	endAssignment(xmldomnode *node,
						stringbuffer *output);
		virtual bool	equals(xmldomnode *node,
						stringbuffer *output);


		// delete...
		virtual bool	deleteQuery(xmldomnode *node,
						stringbuffer *output);
		virtual bool	deleteFrom(xmldomnode *node,
						stringbuffer *output);
		virtual bool	usingClause(xmldomnode *node,
						stringbuffer *output);


		// select...
		virtual bool	selectQuery(xmldomnode *node,
						stringbuffer *output);
		virtual bool	unique(xmldomnode *node,
						stringbuffer *output);
		virtual bool	distinct(xmldomnode *node,
						stringbuffer *output);
		virtual bool	from(xmldomnode *node,
						stringbuffer *output);
		virtual bool	where(xmldomnode *node,
						stringbuffer *output);
		virtual bool	andClause(xmldomnode *node,
						stringbuffer *output);
		virtual bool	orClause(xmldomnode *node,
						stringbuffer *output);
		virtual bool	group(xmldomnode *node,
						stringbuffer *output);
		virtual bool	endGroup(xmldomnode *node,
						stringbuffer *output);
		virtual bool	notClause(xmldomnode *node,
						stringbuffer *output);
		virtual bool	between(xmldomnode *node,
						stringbuffer *output);
		virtual bool	notEquals(xmldomnode *node,
						stringbuffer *output);
		virtual bool	lessThan(xmldomnode *node,
						stringbuffer *output);
		virtual bool	greaterThan(xmldomnode *node,
						stringbuffer *output);
		virtual bool	lessThanOrEqualTo(xmldomnode *node,
						stringbuffer *output);
		virtual bool	greaterThanOrEqualTo(xmldomnode *node,
						stringbuffer *output);
		virtual bool	compliment(xmldomnode *node,
						stringbuffer *output);
		virtual bool	inverse(xmldomnode *node,
						stringbuffer *output);
		virtual bool	plus(xmldomnode *node,
						stringbuffer *output);
		virtual bool	minus(xmldomnode *node,
						stringbuffer *output);
		virtual bool	times(xmldomnode *node,
						stringbuffer *output);
		virtual bool	dividedBy(xmldomnode *node,
						stringbuffer *output);
		virtual bool	bitwiseAnd(xmldomnode *node,
						stringbuffer *output);
		virtual bool	bitwiseOr(xmldomnode *node,
						stringbuffer *output);
		virtual bool	bitwiseXor(xmldomnode *node,
						stringbuffer *output);
		virtual bool	logicalAnd(xmldomnode *node,
						stringbuffer *output);
		virtual bool	logicalOr(xmldomnode *node,
						stringbuffer *output);
		virtual bool	groupBy(xmldomnode *node,
						stringbuffer *output);
		virtual bool	having(xmldomnode *node,
						stringbuffer *output);
		virtual bool	orderBy(xmldomnode *node,
						stringbuffer *output);
		virtual bool	limit(xmldomnode *node,
						stringbuffer *output);
		virtual bool	selectInto(xmldomnode *node,
						stringbuffer *output);
		virtual bool	procedure(xmldomnode *node,
						stringbuffer *output);
		virtual bool	forUpdate(xmldomnode *node,
						stringbuffer *output);


		// set...
		virtual bool	setQuery(xmldomnode *node,
						stringbuffer *output);
		virtual bool	setSession(xmldomnode *node,
						stringbuffer *output);
		virtual bool	setGlobal(xmldomnode *node,
						stringbuffer *output);
		virtual bool	transaction(xmldomnode *node,
						stringbuffer *output);
		virtual bool	isolationLevel(xmldomnode *node,
						stringbuffer *output);



		// helper methods
		virtual bool	outputValue(xmldomnode *node,
						stringbuffer *output);
		virtual bool	space(stringbuffer *output);
		virtual bool	comma(stringbuffer *output);
		virtual bool	leftParen(stringbuffer *output);
		virtual bool	rightParen(stringbuffer *output);
		virtual bool	hasSibling(xmldomnode *node);
		virtual bool	lastWasSpace(stringbuffer *output);

		sqlrconnection_svr *sqlrcon;
		sqlrcursor_svr *sqlrcur;
};

#endif
