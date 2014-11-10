// Copyright (c) 1999-2012  David Muse
// See the file COPYING for more information

#include <sqlrelay/sqlrserverconnection.h>
#include <sqlrelay/sqlrservercursor.h>
#include <sqlrelay/sqlreparser.h>
#include <sqlrelay/sqlrtranslation.h>
#include <debugprint.h>

class forupdatemssqlserverize : public sqlrtranslation {
	public:
			forupdatemssqlserverize(sqlrtranslations *sqlts,
						xmldomnode *parameters,
						bool debug);
		bool	usesTree();
		bool	run(sqlrserverconnection *sqlrcon,
						sqlrservercursor *sqlrcur,
						xmldom *querytree);
};

forupdatemssqlserverize::forupdatemssqlserverize(
					sqlrtranslations *sqlts,
					xmldomnode *parameters,
					bool debug) :
				sqlrtranslation(sqlts,parameters,debug) {
}

bool forupdatemssqlserverize::usesTree() {
	return true;
}

bool forupdatemssqlserverize::run(sqlrserverconnection *sqlrcon,
					sqlrservercursor *sqlrcur,
					xmldom *querytree) {

	xmldomnode	*query=querytree->getRootNode();

	// select query...
	xmldomnode	*selectnode=query->getFirstTagChild(
						sqlreparser::_select);
	if (selectnode->isNullNode()) {
		return true;
	}

	// from...
	xmldomnode	*fromnode=selectnode->getFirstTagChild(
						sqlreparser::_from);
	if (fromnode->isNullNode()) {
		return true;
	}

	// table references...
	xmldomnode	*tablereferencesnode=fromnode->getFirstTagChild(
						sqlreparser::_table_references);
	if (tablereferencesnode->isNullNode()) {
		return true;
	}

	// for update...
	xmldomnode	*forupdatenode=selectnode->getFirstTagChild(
						sqlreparser::_for_update);
	if (forupdatenode->isNullNode()) {
		return true;
	}

	// remove the for update node
	selectnode->deleteChild(forupdatenode);

	// for each table, add a "with (updlock, rowlock)" hint
	for (xmldomnode	*trnode=
			tablereferencesnode->getFirstTagChild(
						sqlreparser::_table_reference);
			!trnode->isNullNode();
			trnode=trnode->getNextTagSibling()) {

		// FIXME: do this properly
		sqlts->newNode(trnode,sqlreparser::_alias,
				"with (updlock, rowlock)");
	}

	return true;
}

extern "C" {
	sqlrtranslation	*new_forupdatemssqlserverize(
					sqlrtranslations *sqlts,
					xmldomnode *parameters,
					bool debug) {
		return new forupdatemssqlserverize(sqlts,parameters,debug);
	}
}
