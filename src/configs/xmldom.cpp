// Copyright (c) 2000-2015  David Muse
// See the file COPYING for more information

#include <config.h>
#include <sqlrelay/sqlrutil.h>
#include <rudiments/xmldom.h>
#include <rudiments/stringbuffer.h>
#include <rudiments/environment.h>
#include <rudiments/directory.h>
#include <rudiments/sys.h>
#include <rudiments/filedescriptor.h>
#include <rudiments/file.h>
#include <rudiments/url.h>
#include <rudiments/filesystem.h>
#include <rudiments/character.h>
#include <rudiments/stdio.h>

#include <defines.h>
#include <defaults.h>
#define DEBUG_MESSAGES
#include <debugprint.h>

class SQLRUTIL_DLLSPEC sqlrconfig_xmldom : public sqlrconfig, public xmldom {
	public:
			sqlrconfig_xmldom();
			~sqlrconfig_xmldom();

		void	getEnabledIds(const char *urlname,
					linkedlist< char * > *idlist);
		bool	load(const char *urlname, const char *id);
		bool	accessible();

		const char * const	*getDefaultAddresses();
		uint64_t		getDefaultAddressCount();
		uint16_t		getDefaultPort();
		const char		*getDefaultSocket();
		bool			getDefaultKrb();
		const char		*getDefaultKrbService();

		bool		getListenOnInet();
		bool		getListenOnUnix();
		const char	*getDbase();
		uint32_t	getConnections();
		uint32_t	getMaxConnections();
		uint32_t	getMaxQueueLength();
		uint32_t	getGrowBy();
		int32_t		getTtl();
		int32_t		getSoftTtl();
		uint16_t	getMaxSessionCount();
		bool		getDynamicScaling();
		const char	*getEndOfSession();
		bool		getEndOfSessionCommit();
		uint32_t	getSessionTimeout();
		const char	*getRunAsUser();
		const char	*getRunAsGroup();
		uint16_t	getCursors();
		uint16_t	getMaxCursors();
		uint16_t	getCursorsGrowBy();
		const char	*getAuthTier();
		bool		getAuthOnConnection();
		bool		getAuthOnDatabase();
		const char	*getSessionHandler();
		const char	*getHandoff();
		const char	*getAllowedIps();
		const char	*getDeniedIps();
		const char	*getDebug();
		bool		getDebugParser();
		bool		getDebugTranslations();
		bool		getDebugFilters();
		bool		getDebugTriggers();
		bool		getDebugBindTranslations();
		bool		getDebugResultSetTranslations();
		uint64_t	getMaxClientInfoLength();
		uint32_t	getMaxQuerySize();
		uint16_t	getMaxBindCount();
		uint16_t	getMaxBindNameLength();
		uint32_t	getMaxStringBindValueLength();
		uint32_t	getMaxLobBindValueLength();
		uint32_t	getMaxErrorLength();
		int32_t		getIdleClientTimeout();
		int64_t		getMaxListeners();
		uint32_t	getListenerTimeout();
		bool		getReLoginAtStart();
		bool		getFakeInputBindVariables();
		bool		getTranslateBindVariables();
		const char	*getIsolationLevel();
		bool		getIgnoreSelectDatabase();
		bool		getWaitForDownDatabase();

		const char	*getDateTimeFormat();
		const char	*getDateFormat();
		const char	*getTimeFormat();
		bool		getDateDdMm();
		bool		getDateYyyyDdMm();
		const char	*getDateDelimiters();
		bool		getIgnoreNonDateTime();

		bool		getKrb();
		const char	*getKrbService();
		const char	*getKrbKeytab();

		linkedlist< char *>	*getSessionStartQueries();
		linkedlist< char *>	*getSessionEndQueries();

		const char	*getParser();
		const char	*getTranslations();
		const char	*getFilters();
		const char	*getResultSetTranslations();
		const char	*getTriggers();
		const char	*getLoggers();
		const char	*getQueries();
		const char	*getPasswordEncryptions();
		const char	*getAuthentications();

		xmldomnode	*getListenersXml();
		xmldomnode	*getParserXml();
		xmldomnode	*getTranslationsXml();
		xmldomnode	*getFiltersXml();
		xmldomnode	*getResultSetTranslationsXml();
		xmldomnode	*getTriggersXml();
		xmldomnode	*getLoggersXml();
		xmldomnode	*getQueriesXml();
		xmldomnode	*getPasswordEncryptionsXml();
		xmldomnode	*getAuthenticationsXml();

		linkedlist< listenercontainer * >	*getListenerList();

		linkedlist< usercontainer * >		*getUserList();

		linkedlist< connectstringcontainer * >	*getConnectStringList();
		connectstringcontainer	*getConnectString(
						const char *connectionid);
		uint32_t		getConnectionCount();
		uint32_t		getMetricTotal();

		linkedlist< routecontainer * >	*getRouteList();
	private:
		bool			getenabledids;
		char			*currentid;
		bool			enabled;
		linkedlist< char * >	*idlist;

		const char	*id;
		bool		foundspecifiedinstance;
		bool		done;

		void	init();
		void	clear();

		void	parseUrl(const char *urlname);
		void	normalizeTree();
		void	getTreeValues();
		uint32_t	atouint32_t(const char *value,
						const char *defaultvalue,
						uint32_t minvalue);
		int32_t		atoint32_t(const char *value,
						const char *defaultvalue,
						int32_t minvalue);
		void	parseDir(const char *dir);
		void	parseLinkFile(const char *urlname);

		bool	tagStart(const char *ns, const char *name);
		bool	tagEnd(const char *ns, const char *name);
		bool	attributeName(const char *name);
		bool	attributeValue(const char *value);
		bool	text(const char *value);

		bool		listenoninet;
		bool		listenonunix;
		const char	*dbase;
		uint32_t	connections;
		uint32_t	maxconnections;
		uint32_t	maxqueuelength;
		uint32_t	growby;
		int32_t		ttl;
		int32_t		softttl;
		uint16_t	maxsessioncount;
		const char	*endofsession;
		bool		endofsessioncommit;
		uint32_t	sessiontimeout;
		const char	*runasuser;
		const char	*runasgroup;
		uint16_t	cursors;
		uint16_t	maxcursors;
		uint16_t	cursorsgrowby;
		const char	*authtier;
		const char	*sessionhandler;
		const char	*handoff;
		bool		authonconnection;
		bool		authondatabase;
		const char	*allowedips;
		const char	*deniedips;
		const char	*debug;
		bool		debugparser;
		bool		debugtranslations;
		bool		debugfilters;
		bool		debugtriggers;
		bool		debugbindtranslations;
		bool		debugresultsettranslations;
		uint64_t	maxclientinfolength;
		uint32_t	maxquerysize;
		uint16_t	maxbindcount;
		uint16_t	maxbindnamelength;
		uint32_t	maxstringbindvaluelength;
		uint32_t	maxlobbindvaluelength;
		uint32_t	maxerrorlength;
		int32_t		idleclienttimeout;
		int64_t		maxlisteners;
		uint32_t	listenertimeout;
		bool		reloginatstart;
		bool		fakeinputbindvariables;
		bool		translatebindvariables;
		const char	*isolationlevel;
		bool		ignoreselectdb;
		bool		waitfordowndb;
		const char	*datetimeformat;
		const char	*dateformat;
		const char	*timeformat;
		bool		dateddmm;
		bool		dateyyyyddmm;
		bool		dateyyyyddmmset;
		const char	*datedelimiters;
		bool		ignorenondatetime;
		bool		krb;
		const char	*krbservice;
		const char	*krbkeytab;

		linkedlist< char *>	sessionstartqueries;
		linkedlist< char *>	sessionendqueries;

		xmldomnode	*listenersxml;
		xmldomnode	*parserxml;
		xmldomnode	*translationsxml;
		xmldomnode	*filtersxml;
		xmldomnode	*resultsettranslationsxml;
		xmldomnode	*triggersxml;
		xmldomnode	*loggersxml;
		xmldomnode	*queriesxml;
		xmldomnode	*pwdencsxml;
		xmldomnode	*authsxml;

		uint32_t	metrictotal;

		linkedlist< listenercontainer * >	listenerlist;
		linkedlist< routecontainer *>		routelist;
		linkedlist< connectstringcontainer * >	connectstringlist;

		listenercontainer	*defaultlistener;

		bool		ininstancetag;
		bool		inidattribute;
		bool		inenabledattribute;
		bool		getattributes;
};

sqlrconfig_xmldom::sqlrconfig_xmldom() : sqlrconfig(), xmldom() {
	debugFunction();

	init();
}

sqlrconfig_xmldom::~sqlrconfig_xmldom() {
	debugFunction();

	clear();
}

void sqlrconfig_xmldom::init() {
	debugFunction();

	getenabledids=false;
	currentid=NULL;
	enabled=false;
	idlist=NULL;
	id=NULL;

	foundspecifiedinstance=false;
	ininstancetag=false;
	inidattribute=false;
	inenabledattribute=false;
	getattributes=true;
	done=false;

	listenoninet=false;
	listenonunix=false;
	dbase=DEFAULT_DBASE;
	connections=charstring::toInteger(DEFAULT_CONNECTIONS);
	maxconnections=0;
	maxqueuelength=charstring::toInteger(DEFAULT_MAXQUEUELENGTH);
	growby=charstring::toInteger(DEFAULT_GROWBY);
	ttl=charstring::toInteger(DEFAULT_TTL);
	softttl=charstring::toInteger(DEFAULT_SOFTTTL);
	maxsessioncount=charstring::toInteger(DEFAULT_MAXSESSIONCOUNT);
	endofsession=DEFAULT_ENDOFSESSION;
	endofsessioncommit=!charstring::compare(endofsession,"commit");
	sessiontimeout=charstring::toUnsignedInteger(DEFAULT_SESSIONTIMEOUT);
	runasuser=DEFAULT_RUNASUSER;
	runasgroup=DEFAULT_RUNASGROUP;
	cursors=charstring::toInteger(DEFAULT_CURSORS);
	maxcursors=charstring::toInteger(DEFAULT_CURSORS);
	cursorsgrowby=charstring::toInteger(DEFAULT_CURSORS_GROWBY);
	authtier=DEFAULT_AUTHTIER;
	authonconnection=charstring::compare(authtier,"database");
	authondatabase=!charstring::compare(authtier,"database");
	sessionhandler=DEFAULT_SESSION_HANDLER;
	handoff=DEFAULT_HANDOFF;
	allowedips=DEFAULT_DENIEDIPS;
	deniedips=DEFAULT_DENIEDIPS;
	debug=DEFAULT_DEBUG;
	debugparser=charstring::contains(debug,"parser");
	debugtranslations=charstring::contains(debug,"translations");
	debugfilters=charstring::contains(debug,"filters");
	debugtriggers=charstring::contains(debug,"triggers");
	debugbindtranslations=charstring::contains(debug,"bindtranslations");
	debugresultsettranslations=
			charstring::contains(debug,"resultsettranslations");
	maxclientinfolength=charstring::toInteger(DEFAULT_MAXCLIENTINFOLENGTH);
	maxquerysize=charstring::toInteger(DEFAULT_MAXQUERYSIZE);
	maxbindcount=charstring::toInteger(DEFAULT_MAXBINDCOUNT);
	maxbindnamelength=charstring::toInteger(DEFAULT_MAXBINDNAMELENGTH);
	maxstringbindvaluelength=charstring::toInteger(
					DEFAULT_MAXSTRINGBINDVALUELENGTH);
	maxlobbindvaluelength=charstring::toInteger(
					DEFAULT_MAXLOBBINDVALUELENGTH);
	maxerrorlength=charstring::toInteger(DEFAULT_MAXERRORLENGTH);
	idleclienttimeout=charstring::toInteger(DEFAULT_IDLECLIENTTIMEOUT);
	metrictotal=0;
	maxlisteners=charstring::toInteger(DEFAULT_MAXLISTENERS);
	listenertimeout=charstring::toUnsignedInteger(DEFAULT_LISTENERTIMEOUT);
	reloginatstart=!charstring::compare(DEFAULT_RELOGINATSTART,"yes");
	fakeinputbindvariables=!charstring::compare(
					DEFAULT_FAKEINPUTBINDVARIABLES,"yes");
	translatebindvariables=!charstring::compare(
					DEFAULT_TRANSLATEBINDVARIABLES,"yes");
	isolationlevel=NULL;
	ignoreselectdb=false;
	waitfordowndb=true;
	datetimeformat=NULL;
	dateformat=NULL;
	timeformat=NULL;
	dateddmm=false;
	dateyyyyddmm=false;
	dateyyyyddmmset=false;
	datedelimiters=DEFAULT_DATEDELIMITERS;
	ignorenondatetime=false;
	krb=false;
	krbservice=DEFAULT_KRBSERVICE;
	krbkeytab=NULL;

	defaultlistener=NULL;
}

void sqlrconfig_xmldom::clear() {
	debugFunction();

	for (listenernode *ln=listenerlist.getFirst(); ln; ln=ln->getNext()) {
		delete ln->getValue();
	}
	listenerlist.clear();

	for (connectstringnode *csn=connectstringlist.getFirst();
						csn; csn=csn->getNext()) {
		delete csn->getValue();
	}
	connectstringlist.clear();

	for (routenode *rn=routelist.getFirst(); rn; rn=rn->getNext()) {
		delete rn->getValue();
	}
	routelist.clear();

	for (linkedlistnode< char * > *ssln=sessionstartqueries.getFirst();
						ssln; ssln=ssln->getNext()) {
		delete[] ssln->getValue();
	}
	sessionstartqueries.clear();

	for (linkedlistnode< char * > *seln=sessionendqueries.getFirst();
						seln; seln=seln->getNext()) {
		delete[] seln->getValue();
	}
	sessionendqueries.clear();
}

const char * const *sqlrconfig_xmldom::getDefaultAddresses() {
	return (defaultlistener)?defaultlistener->getAddresses():NULL;
}

uint64_t sqlrconfig_xmldom::getDefaultAddressCount() {
	return (defaultlistener)?defaultlistener->getAddressCount():0;
}

uint16_t sqlrconfig_xmldom::getDefaultPort() {
	return (defaultlistener)?defaultlistener->getPort():0;
}

const char *sqlrconfig_xmldom::getDefaultSocket() {
	return (defaultlistener)?defaultlistener->getSocket():NULL;
}

bool sqlrconfig_xmldom::getDefaultKrb() {
	return (defaultlistener)?defaultlistener->getKrb():false;
}

const char *sqlrconfig_xmldom::getDefaultKrbService() {
	return (defaultlistener)?defaultlistener->getKrbService():NULL;
}

bool sqlrconfig_xmldom::getListenOnInet() {
	return listenoninet;
}

bool sqlrconfig_xmldom::getListenOnUnix() {
	return listenonunix;
}

const char *sqlrconfig_xmldom::getDbase() {
	return dbase;
}

uint32_t sqlrconfig_xmldom::getConnections() {
	return connections;
}

uint32_t sqlrconfig_xmldom::getMaxConnections() {
	return maxconnections;
}

uint32_t sqlrconfig_xmldom::getMaxQueueLength() {
	return maxqueuelength;
}

uint32_t sqlrconfig_xmldom::getGrowBy() {
	return growby;
}

int32_t sqlrconfig_xmldom::getTtl() {
	return ttl;
}

int32_t sqlrconfig_xmldom::getSoftTtl() {
	return softttl;
}

uint16_t sqlrconfig_xmldom::getMaxSessionCount() {
	return maxsessioncount;
}

bool sqlrconfig_xmldom::getDynamicScaling() {
	return (maxconnections>connections && growby>0 && ttl>-1 &&
		(maxlisteners==-1 || maxqueuelength<=maxlisteners));
}

const char *sqlrconfig_xmldom::getEndOfSession() {
	return endofsession;
}

bool sqlrconfig_xmldom::getEndOfSessionCommit() {
	return endofsessioncommit;
}

uint32_t sqlrconfig_xmldom::getSessionTimeout() {
	return sessiontimeout;
}

const char *sqlrconfig_xmldom::getRunAsUser() {
	return runasuser;
}

const char *sqlrconfig_xmldom::getRunAsGroup() {
	return runasgroup;
}

uint16_t sqlrconfig_xmldom::getCursors() {
	return cursors;
}

uint16_t sqlrconfig_xmldom::getMaxCursors() {
	return maxcursors;
}

uint16_t sqlrconfig_xmldom::getCursorsGrowBy() {
	return cursorsgrowby;
}

const char *sqlrconfig_xmldom::getAuthTier() {
	return authtier;
}

const char *sqlrconfig_xmldom::getSessionHandler() {
	return sessionhandler;
}

const char *sqlrconfig_xmldom::getHandoff() {
	return handoff;
}

bool sqlrconfig_xmldom::getAuthOnConnection() {
	return authonconnection;
}

bool sqlrconfig_xmldom::getAuthOnDatabase() {
	return authondatabase;
}

const char *sqlrconfig_xmldom::getAllowedIps() {
	return allowedips;
}

const char *sqlrconfig_xmldom::getDeniedIps() {
	return deniedips;
}

const char *sqlrconfig_xmldom::getDebug() {
	return debug;
}

bool sqlrconfig_xmldom::getDebugParser() {
	return debugparser;
}

bool sqlrconfig_xmldom::getDebugTranslations() {
	return debugtranslations;
}

bool sqlrconfig_xmldom::getDebugFilters() {
	return debugfilters;
}

bool sqlrconfig_xmldom::getDebugTriggers() {
	return debugtriggers;
}

bool sqlrconfig_xmldom::getDebugBindTranslations() {
	return debugbindtranslations;
}

bool sqlrconfig_xmldom::getDebugResultSetTranslations() {
	return debugresultsettranslations;
}

uint64_t sqlrconfig_xmldom::getMaxClientInfoLength() {
	return maxclientinfolength;
}

uint32_t sqlrconfig_xmldom::getMaxQuerySize() {
	return maxquerysize;
}

uint16_t sqlrconfig_xmldom::getMaxBindCount() {
	return maxbindcount;
}

uint16_t sqlrconfig_xmldom::getMaxBindNameLength() {
	return maxbindnamelength;
}

uint32_t sqlrconfig_xmldom::getMaxStringBindValueLength() {
	return maxstringbindvaluelength;
}

uint32_t sqlrconfig_xmldom::getMaxLobBindValueLength() {
	return maxlobbindvaluelength;
}

uint32_t sqlrconfig_xmldom::getMaxErrorLength() {
	return maxerrorlength;
}

int32_t sqlrconfig_xmldom::getIdleClientTimeout() {
	return idleclienttimeout;
}

int64_t sqlrconfig_xmldom::getMaxListeners() {
	return maxlisteners;
}

uint32_t sqlrconfig_xmldom::getListenerTimeout() {
	return listenertimeout;
}

bool sqlrconfig_xmldom::getReLoginAtStart() {
	return reloginatstart;
}

bool sqlrconfig_xmldom::getFakeInputBindVariables() {
	return fakeinputbindvariables;
}

bool sqlrconfig_xmldom::getTranslateBindVariables() {
	return translatebindvariables;
}

const char *sqlrconfig_xmldom::getIsolationLevel() {
	return isolationlevel;
}

bool sqlrconfig_xmldom::getIgnoreSelectDatabase() {
	return ignoreselectdb;
}

bool sqlrconfig_xmldom::getWaitForDownDatabase() {
	return waitfordowndb;
}

const char *sqlrconfig_xmldom::getDateTimeFormat() {
	return datetimeformat;
}

const char *sqlrconfig_xmldom::getDateFormat() {
	return dateformat;
}

const char *sqlrconfig_xmldom::getTimeFormat() {
	return timeformat;
}

bool sqlrconfig_xmldom::getDateDdMm() {
	return dateddmm;
}

bool sqlrconfig_xmldom::getDateYyyyDdMm() {
	return dateyyyyddmm;
}

const char *sqlrconfig_xmldom::getDateDelimiters() {
	return datedelimiters;
}

bool sqlrconfig_xmldom::getIgnoreNonDateTime() {
	return ignorenondatetime;
}

bool sqlrconfig_xmldom::getKrb() {
	return krb;
}

const char *sqlrconfig_xmldom::getKrbService() {
	return krbservice;
}

const char *sqlrconfig_xmldom::getKrbKeytab() {
	return krbkeytab;
}

linkedlist< char * > *sqlrconfig_xmldom::getSessionStartQueries() {
	return &sessionstartqueries;
}

linkedlist< char * > *sqlrconfig_xmldom::getSessionEndQueries() {
	return &sessionendqueries;
}

const char *sqlrconfig_xmldom::getParser() {
	return NULL;
}

const char *sqlrconfig_xmldom::getTranslations() {
	return NULL;
}

const char *sqlrconfig_xmldom::getFilters() {
	return NULL;
}

const char *sqlrconfig_xmldom::getResultSetTranslations() {
	return NULL;
}

const char *sqlrconfig_xmldom::getTriggers() {
	return NULL;
}

const char *sqlrconfig_xmldom::getLoggers() {
	return NULL;
}

const char *sqlrconfig_xmldom::getQueries() {
	return NULL;
}

const char *sqlrconfig_xmldom::getPasswordEncryptions() {
	return NULL;
}

const char *sqlrconfig_xmldom::getAuthentications() {
	return NULL;
}

xmldomnode *sqlrconfig_xmldom::getListenersXml() {
	return listenersxml;
}

xmldomnode *sqlrconfig_xmldom::getParserXml() {
	return parserxml;
}

xmldomnode *sqlrconfig_xmldom::getTranslationsXml() {
	return translationsxml;
}

xmldomnode *sqlrconfig_xmldom::getFiltersXml() {
	return filtersxml;
}

xmldomnode *sqlrconfig_xmldom::getResultSetTranslationsXml() {
	return resultsettranslationsxml;
}

xmldomnode *sqlrconfig_xmldom::getTriggersXml() {
	return triggersxml;
}

xmldomnode *sqlrconfig_xmldom::getLoggersXml() {
	return loggersxml;
}

xmldomnode *sqlrconfig_xmldom::getQueriesXml() {
	return queriesxml;
}

xmldomnode *sqlrconfig_xmldom::getPasswordEncryptionsXml() {
	return pwdencsxml;
}

xmldomnode *sqlrconfig_xmldom::getAuthenticationsXml() {
	return authsxml;
}

linkedlist< listenercontainer * > *sqlrconfig_xmldom::getListenerList() {
	return NULL;
}

linkedlist< usercontainer * > *sqlrconfig_xmldom::getUserList() {
	return NULL;
}

linkedlist< connectstringcontainer * > *sqlrconfig_xmldom::
						getConnectStringList() {
	return &connectstringlist;
}

connectstringcontainer *sqlrconfig_xmldom::getConnectString(
						const char *connectionid) {
	for (connectstringnode *csn=connectstringlist.getFirst();
						csn; csn=csn->getNext()) {
		if (!charstring::compare(connectionid,
					csn->getValue()->getConnectionId())) {
			return csn->getValue();
		}
	}
	return NULL;
}

uint32_t sqlrconfig_xmldom::getConnectionCount() {
	return connectstringlist.getLength();
}

uint32_t sqlrconfig_xmldom::getMetricTotal() {
	// This is tallied here instead of whenever the parser runs into a
	// metric attribute because people often forget to include metric
	// attributes.  In that case, though each connection has a metric,
	// metrictotal=0, causing no connections to start.
	if (!metrictotal) {
		for (connectstringnode *csn=connectstringlist.getFirst();
						csn; csn=csn->getNext()) {
			metrictotal=metrictotal+csn->getValue()->getMetric();
		}
	}
	return metrictotal;
}

linkedlist< routecontainer * >	*sqlrconfig_xmldom::getRouteList() {
	return &routelist;
}

bool sqlrconfig_xmldom::tagStart(const char *ns, const char *name) {
	debugFunction();

	debugPrintf("<%s>\n",name);

	// bail if we're already done
	if (done) {
		debugPrintf("  already done\n");
		return true;
	}

	// is this an instance tag?
	ininstancetag=!charstring::compare(name,"instance");

	if (ininstancetag) {

		debugPrintf("  in instance tag\n");

		// re-init enabled flag
		enabled=false;

		// re-init get attributes flag
		getattributes=true;

	} else {

		debugPrintf("  not in instance tag\n");

		// bail if we haven't found the specified instance yet
		if (!foundspecifiedinstance) {
			debugPrintf("  haven't found specified instance yet\n");
			return true;
		}
	}

	return (getenabledids)?true:xmldom::tagStart(ns,name);
}

bool sqlrconfig_xmldom::tagEnd(const char *ns, const char *name) {
	debugFunction();

	debugPrintf("<%s>\n",name);

	// bail if we're already done
	if (done) {
		debugPrintf("  already done\n");
		return true;
	}

	// bail if we haven't found the specified instance yet
	// unless we're closing an instance tag
	if (!foundspecifiedinstance && charstring::compare(name,"instance")) {
		debugPrintf("  haven't found specified instance yet\n");
		return true;
	}

	// if we've found the specified instance at this point then we're done
	if (!getenabledids && foundspecifiedinstance &&
				!charstring::compare(name,"instance")) {
		debugPrintf("  found specified instance\n");
		done=true;
	}

	return (getenabledids)?true:xmldom::tagEnd(ns,name);
}

bool sqlrconfig_xmldom::attributeName(const char *name) {
	debugFunction();

	debugPrintf("attribute name=%s\n",name);

	// bail if we're not supposed to get attributes
	if (!getattributes) {
		debugPrintf("  not getting attributes\n");
		return true;
	}

	// bail if we're already done
	if (done) {
		debugPrintf("  already done\n");
		return true;
	}

	// bail if we're not in an instance tag and
	// we haven't found the specified instance yet
	if (!ininstancetag && !foundspecifiedinstance) {
		debugPrintf("  not in instance tag, "
				"haven't found specified instance yet\n");
		return true;
	}

	// check for id and enabled attributes of the instance tag
	inidattribute=(ininstancetag &&
				!charstring::compare(name,"id"));
	inenabledattribute=(ininstancetag &&
				!charstring::compare(name,"enabled"));
	debugPrintf("  inidattribute=%d  inenabledattribute=%d\n",
					inidattribute,inenabledattribute);

	return (getenabledids)?true:xmldom::attributeName(name);
}

bool sqlrconfig_xmldom::attributeValue(const char *value) {
	debugFunction();

	debugPrintf("attribute value=\"%s\"\n",value);

	// bail if we're not supposed to get attributes
	if (!getattributes) {
		debugPrintf("  not getting attributes\n");
		return true;
	}

	// bail if we're already done
	if (done) {
		debugPrintf("  already done\n");
		return true;
	}

	// bail if we're not in an instance tag and
	// we haven't found the specified instance yet
	if (!ininstancetag && !foundspecifiedinstance) {
		debugPrintf("  not in instance tag, "
				"haven't found specified instance yet\n");
		return true;
	}

	if (getenabledids) {

		// set the current id
		if (inidattribute) {
			delete[] currentid;
			currentid=charstring::duplicate(value);
			debugPrintf("  setting current id to \"%s\"\n",
								currentid);
		}

		// if this instance is enabled, then add its id to the id list
		if (inenabledattribute && !charstring::compare(value,"yes")) {
			idlist->append(charstring::duplicate(currentid));
		}

	} else {

		// check for the specified instance, if we haven't found it yet
		if (!foundspecifiedinstance) {
			foundspecifiedinstance=
				(inidattribute && value &&
					!charstring::compare(value,id));
		}

		// bail if we haven't found the specified instance,
		// unless we're in an instance tag
		if (!foundspecifiedinstance && !ininstancetag) {
			return true;
		}

		// if this is an id attribute but it wasn't the one we were
		// looking for, then disable getting the rest of the
		// attributes for this tag
		if (!foundspecifiedinstance && inidattribute) {
			getattributes=false;
		}
	}

	return (getenabledids)?true:xmldom::attributeValue(value);
}

bool sqlrconfig_xmldom::text(const char *value) {
	debugFunction();

	debugPrintf("  text: %s\n",value);

	// bail if we're already done
	if (done) {
		debugPrintf("  already done\n");
		return true;
	}

	// bail if we haven't found the specified instance yet
	if (!foundspecifiedinstance) {
		debugPrintf("  haven't found specified instance yet\n");
		return true;
	}

	// bail if the text is entirely whitespace
	for (const char *c=value; *c; c++) {
		if (!character::isWhitespace(*c)) {
			return xmldom::text(value);
		}
	}
	debugPrintf("  entirely whitespce, removing\n");
	return true;
}

bool sqlrconfig_xmldom::load(const char *urlname, const char *id) {
	debugFunction();

	debugPrintf("urlname=\"%s\"  id=\"%s\"\n",urlname,id);

	// sanity check
	if (charstring::isNullOrEmpty(urlname) ||
			charstring::isNullOrEmpty(id)) {
		return false;
	}

	// re-init
	clear();
	init();

	// set some stateful variables
	getenabledids=false;
	this->id=id;
	foundspecifiedinstance=false;
	done=false;

	// parse the url
	parseUrl(urlname);

	#ifdef DEBUG_MESSAGES
		debugPrintf("\noriginal tree:\n");
		getRootNode()->print(&stdoutput);
		debugPrintf("\n");
	#endif

	// normalize the tree
	normalizeTree();

	#ifdef DEBUG_MESSAGES
		debugPrintf("normalized tree:\n");
		getRootNode()->print(&stdoutput);
		debugPrintf("\n");
	#endif

	// get values from the tree
	getTreeValues();

	return foundspecifiedinstance;
}

void sqlrconfig_xmldom::normalizeTree() {

	// prune instances for non-specified id's
	xmldomnode *instance=getRootNode()->getFirstTagChild("instance");
	while (!instance->isNullNode()) {
		xmldomnode	*next=instance->getNextTagSibling("instance");
		if (charstring::compare(instance->getAttributeValue("id"),id)) {
			instance->getParent()->deleteChild(instance);
		}
		instance=next;
	}

	// update...

	// get the instance
	instance=getRootNode()->getFirstTagChild("instance");

	// addresses="" -> addresses="0.0.0.0"
	xmldomnode	*attr=instance->getAttribute("addresses");
	if (!attr->isNullNode()) {
		if (charstring::isNullOrEmpty(attr->getValue())) {
			attr->setValue("0.0.0.0");
		}
	}

	// unixport -> socket
	attr=instance->getAttribute("unixport");
	if (!attr->isNullNode()) {
		attr->setName("socket");
	}

	// authentication -> authtier
	attr=instance->getAttribute("authentication");
	if (!attr->isNullNode()) {
		attr->setName("authtier");
	}

	// oracle8 -> oracle, sybase -> sap
	attr=instance->getAttribute("dbase");
	if (!attr->isNullNode()) {
		if (!charstring::compare(attr->getValue(),"oracle8")) {
			attr->setValue("oracle");
		} else if (!charstring::compare(attr->getValue(),"sybase")) {
			attr->setValue("sap");
		}
	}

	// missing listeners tag
	xmldomnode	*listeners=instance->getFirstTagChild("listeners");
	if (listeners->isNullNode()) {
		listeners=instance->insertTag("listeners",0);
	}

	// instance.addresses/port/socket/etc. -> listener
	xmldomnode	*addresses=instance->getAttribute("addresses");
	xmldomnode	*port=instance->getAttribute("port");
	xmldomnode	*socket=instance->getAttribute("socket");
	xmldomnode	*krb=instance->getAttribute("krb");
	xmldomnode	*krbservice=instance->getAttribute("krbservice");
	xmldomnode	*krbkeytab=instance->getAttribute("krbkeytab");
	if (!addresses->isNullNode() ||
			!port->isNullNode() ||
			!socket->isNullNode() ||
			!krb->isNullNode() ||
			!krbservice->isNullNode() ||
			!krbkeytab->isNullNode()) {

		xmldomnode	*listener=listeners->insertTag("listener",0);
		listener->setAttributeValue("protocol",DEFAULT_PROTOCOL);

		if (!addresses->isNullNode()) {
			listener->setAttributeValue(addresses->getName(),
							addresses->getValue());
			instance->deleteAttribute(addresses);
		}
		if (!port->isNullNode()) {
			listener->setAttributeValue(port->getName(),
							port->getValue());
			instance->deleteAttribute(port);
		}
		if (!socket->isNullNode()) {
			listener->setAttributeValue(socket->getName(),
							socket->getValue());
			instance->deleteAttribute(socket);
		}
		if (!krb->isNullNode()) {
			listener->setAttributeValue(krb->getName(),
							krb->getValue());
			instance->deleteAttribute(krb);
		}
		if (!krbservice->isNullNode()) {
			listener->setAttributeValue(krbservice->getName(),
							krbservice->getValue());
			instance->deleteAttribute(krbservice);
		}
		if (!krbkeytab->isNullNode()) {
			listener->setAttributeValue(krbkeytab->getName(),
							krbkeytab->getValue());
			instance->deleteAttribute(krbkeytab);
		}
	}

	// empty listeners tag
	if (listeners->getFirstTagChild("listener")->isNullNode()) {
		xmldomnode	*listener=listeners->appendTag("listener");
		listener->setAttributeValue("protocol",DEFAULT_PROTOCOL);
	}
	
	// normalize address, port, socket...
	for (xmldomnode *listener=listeners->getFirstTagChild("listener");
			!listener->isNullNode();
			listener=listener->getNextTagSibling("listener")) {

		bool	hasaddresses=!listener->
				getAttribute("addresses")->isNullNode();
		bool	hasport=!listener->
				getAttribute("port")->isNullNode();
		bool	hassocket=!listener->
				getAttribute("socket")->isNullNode();

		// nothing specified -> default address, default port, no socket
		if (!hasaddresses && !hasport && !hassocket) {
			listener->setAttributeValue(
					"addresses",DEFAULT_ADDRESS);
			listener->setAttributeValue(
					"port",DEFAULT_PORT);
		} else

		// port but no address -> default address
		if (!hasaddresses && hasport) {
			listener->setAttributeValue(
					"addresses",DEFAULT_ADDRESS);
		} else

		// address but no port -> default port
		if (!hasaddresses && hasport) {
			listener->setAttributeValue(
					"port",DEFAULT_PORT);
		}
	}

	// missing authentications tag
	xmldomnode	*authentications=
				instance->getFirstTagChild("authentications");
	if (authentications->isNullNode()) {
		authentications=instance->insertTag("authentications",1);
	}

	//  users -> auth_userlist
	xmldomnode	*users=instance->getFirstTagChild("users");
	if (!users->isNullNode()) {

		xmldomnode	*authentication=
				authentications->insertTag("authentication",0);
		authentication->setAttributeValue("module","userlist");

		for (xmldomnode *user=users->getFirstTagChild("user");
				!user->isNullNode();
				user=user->getNextTagSibling("user")) {

			xmldomnode	*authuser=
					authentication->appendTag("user");

			xmldomnode	*userattr=
					user->getAttribute("user");
			if (!userattr->isNullNode()) {
				authuser->setAttributeValue(
						"user",
						userattr->getValue());
			}

			xmldomnode	*passwordattr=
					user->getAttribute("password");
			if (!passwordattr->isNullNode()) {
				authuser->setAttributeValue(
						"password",
						passwordattr->getValue());
			}

			// passwordencryption -> passwordencryptionid
			xmldomnode	*pwdencidattr=
					user->getAttribute(
						"passwordencryptionid");
			if (pwdencidattr->isNullNode()) {
				pwdencidattr=
					user->getAttribute(
						"passwordencryption");
			}
			if (!pwdencidattr->isNullNode()) {
				authuser->setAttributeValue(
						"passwordencryptionid",
						pwdencidattr->getValue());
			}
		}

		users->getParent()->deleteChild(users);
	}

	// connections...
	uint32_t	connectioncount=0;
	xmldomnode	*conns=instance->getFirstTagChild("connections");
	for (xmldomnode *conn=conns->getFirstTagChild("connection");
			!conn->isNullNode();
			conn=conn->getNextTagSibling("connection")) {

		// connection id
		const char	*connid=conn->getAttributeValue("connectionid");
		if (charstring::isNullOrEmpty(connid)) {
			stringbuffer	connectionid;
			connectionid.append(id)->append('-');
			connectionid.append(connectioncount);
			conn->setAttributeValue("connectionid",
						connectionid.getString());
			connectioncount++;
		}

		// passwordencryption -> passwordencryptionid
		xmldomnode	*pwdencattr=
				conn->getAttribute("passwordencryption");
		if (!pwdencattr->isNullNode()) {
			pwdencattr->setName("passwordencryptionid");
		}
	}

	// FIXME: authtier="database" -> auth_database

	// FIXME: datetimeformat -> resultsettranslation
}

void sqlrconfig_xmldom::getTreeValues() {

	// instance tag...
	xmldomnode	*instance=getRootNode()->getFirstTagChild("instance");
	xmldomnode	*attr=instance->getAttribute("dbase");
	if (!attr->isNullNode()) {
		dbase=attr->getValue();
	}
	attr=instance->getAttribute("connections");
	if (!attr->isNullNode()) {
		connections=atouint32_t(attr->getValue(),
						DEFAULT_CONNECTIONS,0);
		if (connections>MAXCONNECTIONS) {
			connections=MAXCONNECTIONS;
		}
		if (maxconnections<connections) {
			maxconnections=connections;
		}
	}
	attr=instance->getAttribute("maxconnections");
	if (!attr->isNullNode()) {
		maxconnections=atouint32_t(attr->getValue(),
						DEFAULT_CONNECTIONS,1);
		if (maxconnections>MAXCONNECTIONS) {
			maxconnections=MAXCONNECTIONS;
		}
		if (maxconnections<connections) {
			maxconnections=connections;
		}
	}
	attr=instance->getAttribute("maxqueuelength");
	if (!attr->isNullNode()) {
		maxqueuelength=atouint32_t(attr->getValue(),
						DEFAULT_MAXQUEUELENGTH,0);
	}
	attr=instance->getAttribute("growby");
	if (!attr->isNullNode()) {
		growby=atouint32_t(attr->getValue(),DEFAULT_GROWBY,1);
	}
	attr=instance->getAttribute("ttl");
	if (!attr->isNullNode()) {
		ttl=atoint32_t(attr->getValue(),DEFAULT_TTL,0);
	}
	attr=instance->getAttribute("softttl");
	if (!attr->isNullNode()) {
		softttl=atoint32_t(attr->getValue(),DEFAULT_SOFTTTL,0);
	}
	attr=instance->getAttribute("maxsessioncount");
	if (!attr->isNullNode()) {
		maxsessioncount=atouint32_t(attr->getValue(),
						DEFAULT_MAXSESSIONCOUNT,0);
	}
	attr=instance->getAttribute("endofsession");
	if (!attr->isNullNode()) {
		endofsession=attr->getValue();
		endofsessioncommit=!charstring::compare(endofsession,"commit");
	}
	attr=instance->getAttribute("sessiontimeout");
	if (!attr->isNullNode()) {
		sessiontimeout=atouint32_t(attr->getValue(),
						DEFAULT_SESSIONTIMEOUT,1);
	}
	attr=instance->getAttribute("runasuser");
	if (!attr->isNullNode()) {
		runasuser=attr->getValue();
	}
	attr=instance->getAttribute("runasgroup");
	if (!attr->isNullNode()) {
		runasgroup=attr->getValue();
	}
	attr=instance->getAttribute("cursors");
	if (!attr->isNullNode()) {
		cursors=atouint32_t(attr->getValue(),DEFAULT_CURSORS,0);
		if (maxcursors<cursors) {
			maxcursors=cursors;
		}
	}
	attr=instance->getAttribute("maxcursors");
	if (!attr->isNullNode()) {
		maxcursors=atouint32_t(attr->getValue(),DEFAULT_CURSORS,0);
		if (maxcursors<cursors) {
			maxcursors=cursors;
		}
	}
	attr=instance->getAttribute("cursors_growby");
	if (!attr->isNullNode()) {
		cursorsgrowby=atouint32_t(attr->getValue(),
						DEFAULT_CURSORS_GROWBY,1);
	}
	attr=instance->getAttribute("authtier");
	if (!attr->isNullNode()) {
		authtier=attr->getValue();
		authondatabase=!charstring::compare(authtier,"database");
		authonconnection=charstring::compare(authtier,"database");
	}
	attr=instance->getAttribute("sessionhandler");
	if (!attr->isNullNode()) {
		sessionhandler=attr->getValue();
	}
	attr=instance->getAttribute("handoff");
	if (!attr->isNullNode()) {
		handoff=attr->getValue();
	}
	attr=instance->getAttribute("allowedips");
	if (!attr->isNullNode()) {
		allowedips=attr->getValue();
	}
	attr=instance->getAttribute("deniedips");
	if (!attr->isNullNode()) {
		deniedips=attr->getValue();
	}
	attr=instance->getAttribute("debug");
	if (!attr->isNullNode()) {
		debug=attr->getValue();
		debugparser=charstring::contains(debug,"parser");
		debugtranslations=charstring::contains(debug,"translations");
		debugfilters=charstring::contains(debug,"filters");
		debugtriggers=charstring::contains(debug,"triggers");
		debugbindtranslations=
			charstring::contains(debug,"bindtranslations");
		debugresultsettranslations=
			charstring::contains(debug,"resultsettranslations");
	}
	attr=instance->getAttribute("maxclientinfolength");
	if (!attr->isNullNode()) {
		maxclientinfolength=charstring::toInteger(attr->getValue());
	}
	attr=instance->getAttribute("maxquerysize");
	if (!attr->isNullNode()) {
		maxquerysize=charstring::toInteger(attr->getValue());
	}
	attr=instance->getAttribute("maxbindcount");
	if (!attr->isNullNode()) {
		maxbindcount=charstring::toInteger(attr->getValue());
	}
	attr=instance->getAttribute("maxbindnamelength");
	if (!attr->isNullNode()) {
		maxbindnamelength=charstring::toInteger(attr->getValue());
	}
	attr=instance->getAttribute("maxstringbindvaluelength");
	if (!attr->isNullNode()) {
		maxstringbindvaluelength=
				charstring::toInteger(attr->getValue());
	}
	attr=instance->getAttribute("maxlobbindvaluelength");
	if (!attr->isNullNode()) {
		maxlobbindvaluelength=charstring::toInteger(attr->getValue());
	}
	attr=instance->getAttribute("maxerrorlength");
	if (!attr->isNullNode()) {
		maxerrorlength=charstring::toInteger(attr->getValue());
	}
	attr=instance->getAttribute("idleclienttimeout");
	if (!attr->isNullNode()) {
		idleclienttimeout=charstring::toInteger(attr->getValue());
	}
	attr=instance->getAttribute("maxlisteners");
	if (!attr->isNullNode()) {
		maxlisteners=charstring::toInteger(attr->getValue());
	}
	attr=instance->getAttribute("listenertimeout");
	if (!attr->isNullNode()) {
		listenertimeout=charstring::toUnsignedInteger(attr->getValue());
	}
	attr=instance->getAttribute("reloginatstart");
	if (!attr->isNullNode()) {
		reloginatstart=!charstring::compare(attr->getValue(),"yes");
	}
	attr=instance->getAttribute("fakeinputbindvariables");
	if (!attr->isNullNode()) {
		fakeinputbindvariables=!charstring::compare(
						attr->getValue(),"yes");
	}
	attr=instance->getAttribute("translatebindvariables");
	if (!attr->isNullNode()) {
		translatebindvariables=!charstring::compare(
						attr->getValue(),"yes");
	}
	attr=instance->getAttribute("isolationlevel");
	if (!attr->isNullNode()) {
		isolationlevel=attr->getValue();
	}
	attr=instance->getAttribute("ignoreselectdb");
	if (!attr->isNullNode()) {
		ignoreselectdb=!charstring::compare(attr->getValue(),"yes");
	}
	attr=instance->getAttribute("waitfordowndb");
	if (!attr->isNullNode()) {
		waitfordowndb=!charstring::compare(attr->getValue(),"yes");
	}
	attr=instance->getAttribute("datatimeformat");
	if (!attr->isNullNode()) {
		datetimeformat=attr->getValue();
		if (!dateformat) {
			dateformat=attr->getValue();
		}
		if (!timeformat) {
			timeformat=attr->getValue();
		}
	}
	attr=instance->getAttribute("dateformat");
	if (!attr->isNullNode()) {
		dateformat=attr->getValue();
		if (!datetimeformat) {
			datetimeformat=attr->getValue();
		}
		if (!timeformat) {
			timeformat=attr->getValue();
		}
	}
	attr=instance->getAttribute("timeformat");
	if (!attr->isNullNode()) {
		timeformat=attr->getValue();
		if (!datetimeformat) {
			datetimeformat=attr->getValue();
		}
		if (!dateformat) {
			dateformat=attr->getValue();
		}
	}
	attr=instance->getAttribute("dateddmm");
	if (!attr->isNullNode()) {
		dateddmm=!charstring::compare(attr->getValue(),"yes");
		if (!dateyyyyddmmset) {
			dateyyyyddmm=dateddmm;
		}
	}
	attr=instance->getAttribute("dateyyyyddmm");
	if (!attr->isNullNode()) {
		dateyyyyddmm=!charstring::compare(attr->getValue(),"yes");
		dateyyyyddmmset=true;
	}
	attr=instance->getAttribute("datedelimiters");
	if (!attr->isNullNode()) {
		datedelimiters=attr->getValue();
	}
	attr=instance->getAttribute("ignorenondatetime");
	if (!attr->isNullNode()) {
		ignorenondatetime=!charstring::compare(attr->getValue(),"yes");
	}
	attr=instance->getAttribute("krb");
	if (!attr->isNullNode()) {
		krb=!charstring::compare(attr->getValue(),"yes");
	}
	attr=instance->getAttribute("krbservice");
	if (!attr->isNullNode()) {
		krbservice=attr->getValue();
	}
	attr=instance->getAttribute("krbkeytab");
	if (!attr->isNullNode()) {
		krbkeytab=attr->getValue();
	}


	// xmls...
	listenersxml=instance->getFirstTagChild("listeners");
	parserxml=instance->getFirstTagChild("parser");
	translationsxml=instance->getFirstTagChild("translations");
	filtersxml=instance->getFirstTagChild("filters");
	resultsettranslationsxml=instance->getFirstTagChild(
						"resultsettranslations");
	triggersxml=instance->getFirstTagChild("triggers");
	loggersxml=instance->getFirstTagChild("loggers");
	queriesxml=instance->getFirstTagChild("queries");
	pwdencsxml=instance->getFirstTagChild("pwdencs");
	authsxml=instance->getFirstTagChild("auths");


	// listeners tag...
	for (xmldomnode *listener=listenersxml->getFirstTagChild("listener");
			!listener->isNullNode();
			listener=listener->getNextTagSibling("listener")) {

		// listen on inet/unix...
		if (!listener->getAttribute("port")->isNullNode()) {
			listenoninet=true;
		}
		if (!listener->getAttribute("socket")->isNullNode()) {
			listenonunix=true;
		}

		// add an item to the listener list
		listenercontainer	*l=new listenercontainer();
		const char	*addresses=
				listener->getAttributeValue("addresses");
		if (charstring::isNullOrEmpty(addresses)) {
			addresses=DEFAULT_ADDRESS;
		}
		char		**addr=NULL;
		uint64_t	addrcount=0;
		charstring::split(addresses,",",true,&addr,&addrcount);
		uint64_t	index;
		for (index=0; index<addrcount; index++) {
			charstring::bothTrim(addr[index]);
		}
		l->setAddresses(addr,addrcount);
		l->setPort(atouint32_t(
				listener->getAttributeValue("port"),"0",0));
		l->setSocket(listener->getAttributeValue("socket"));
		l->setKrb(!charstring::compare(
				listener->getAttributeValue("krb"),"yes"));
		l->setKrbService(listener->getAttributeValue("krbservice"));
		l->setKrbKeytab(listener->getAttributeValue("krbkeytab"));
		listenerlist.append(l);
	}

	// get the default listener...
	// use the first listener for the default protocol,
	// or just use the first listener if that doesn't work
	for (listenernode *node=listenerlist.getFirst();
				node; node=node->getNext()) {
		listenercontainer	*l=node->getValue();
		if (!charstring::compare(l->getProtocol(),DEFAULT_PROTOCOL)) {
			defaultlistener=l;
			break;
		}
	}
	if (!defaultlistener) {
		defaultlistener=listenerlist.getFirst()->getValue();
	}


	// session queries
	xmldomnode	*session=instance->getFirstTagChild("session");
	xmldomnode	*start=session->getFirstTagChild("start");
	for (xmldomnode *runquery=start->getFirstTagChild("runquery");
			!runquery->isNullNode();
			runquery=runquery->getNextTagSibling("runquery")) {
		sessionstartqueries.append(charstring::duplicate(
				runquery->getFirstChild("text")->getValue()));
	}
	xmldomnode	*end=session->getFirstTagChild("end");
	for (xmldomnode *runquery=end->getFirstTagChild("runquery");
			!runquery->isNullNode();
			runquery=runquery->getNextTagSibling("runquery")) {
		sessionendqueries.append(charstring::duplicate(
				runquery->getFirstChild("text")->getValue()));
	}


	// connect string list
	for (xmldomnode *connection=instance->
					getFirstTagChild("connections")->
					getFirstTagChild("connection");
			!connection->isNullNode();
			connection=connection->
					getNextTagSibling("connection")) {
		
		// add an item to the connect string list
		connectstringcontainer	*c=new connectstringcontainer();
		const char	*connectionid=connection->
				getAttributeValue("connectionid");
		const char	*str=connection->
				getAttributeValue("string");
		const char	*metric=connection->
				getAttributeValue("metric");
		const char	*blb=connection->
				getAttributeValue("behindloadbalancer");
		const char	*pwdencid=connection->
				getAttributeValue("passwordencrpytionid");
		c->setConnectionId(connectionid);
		c->setString((str)?str:DEFAULT_CONNECTSTRING);
		c->parseConnectString();
		c->setMetric(atouint32_t(metric,DEFAULT_METRIC,1));
		c->setBehindLoadBalancer(!charstring::compare(blb,"yes"));
		c->setPasswordEncryption(pwdencid);
		connectstringlist.append(c);
	}


	// FIXME: route list
}

uint32_t sqlrconfig_xmldom::atouint32_t(const char *value,
				const char *defaultvalue, uint32_t minvalue) {
	uint32_t	retval=charstring::toUnsignedInteger(
						(value)?value:defaultvalue);
	if (retval<minvalue) {
		retval=charstring::toUnsignedInteger(defaultvalue);
	}
	return retval;
}

int32_t sqlrconfig_xmldom::atoint32_t(const char *value,
				const char *defaultvalue, int32_t minvalue) {
	int32_t	retval=charstring::toInteger((value)?value:defaultvalue);
	if (retval<minvalue) {
		retval=charstring::toInteger(defaultvalue);
	}
	return retval;
}

void sqlrconfig_xmldom::parseUrl(const char *urlname) {
	debugFunction();

	// skip leading whitespace
	while (*urlname && character::isWhitespace(*urlname)) {
		urlname++;
	}

	// bump past xmldom protocol identifiers
	if (!charstring::compare(urlname,"xmldom://",9)) {
		urlname+=9;
	} else if (!charstring::compare(urlname,"xmldom:",7)) {
		urlname+=7;
	}

	debugPrintf("urlname=\"%s\"\n",urlname);

	// parse the url as a config directory, config file or link file
	if (!charstring::compare(urlname,"dir:",4)) {
		parseDir(urlname);
	} else {
		debugPrintf("parseFile()...\n");
		if (!parseFile(urlname)) {
			debugPrintf("failed...\n");
			parseLinkFile(urlname);
		}
	}
}

void sqlrconfig_xmldom::parseDir(const char *urlname) {
	debugFunction();

	debugPrintf("urlname=\"%s\"\n",urlname);

	// skip the protocol
	const char	*dir=
		(!charstring::compare(urlname,"dir://",6))?
					(urlname+6):(urlname+4);

	// attempt to parse files in the config dir
	directory	d;
	stringbuffer	fullpath;
	const char	*slash=(!charstring::compareIgnoringCase(
					sys::getOperatingSystemName(),
					"Windows"))?"\\":"/";
	if (!done && d.open(dir)) {
		for (;;) {
			char	*filename=d.read();
			if (!filename) {
				break;
			}
			if (charstring::compare(filename,".") &&
				charstring::compare(filename,"..")) {

				fullpath.clear();
				fullpath.append(dir);
				fullpath.append(slash);
				fullpath.append(filename);
				delete[] filename;

				parseFile(fullpath.getString());
			}
		}
	}
	d.close();
}

void sqlrconfig_xmldom::parseLinkFile(const char *urlname) {
	debugFunction();

	// process the file "urlname" as a list of urls...
	filedescriptor	*fd=NULL;
	file	fl;
	url	u;

	// bump past file protocol identifiers
	if (!charstring::compare(urlname,"file://",7)) {
		urlname+=7;
	} else if (!charstring::compare(urlname,"file:",5)) {
		urlname+=5;
	}

	// bump past xmldom protocol identifiers
	if (!charstring::compare(urlname,"xmldom://",9)) {
		urlname+=9;
	} else if (!charstring::compare(urlname,"xmldom:",7)) {
		urlname+=7;
	}

	debugPrintf("urlname=\"%s\"\n",urlname);

	// parse file or url...
	if (charstring::contains(urlname,"://")) {

		// open the url
		if (!u.open(urlname,O_RDONLY)) {
			return;
		}

		// set fd
		fd=&u;

	} else {

		// open the file
		if (!fl.open(urlname,O_RDONLY)) {
			return;
		}

		// optimize
		filesystem	fs;
		if (fs.initialize(urlname)) {
			fl.setReadBufferSize(fs.getOptimumTransferBlockSize());
		}
		fl.sequentialAccess(0,fl.getSize());
		fl.onlyOnce(0,fl.getSize());

		// set fd
		fd=&fl;
	}

	// read lines from the file
	char	*line=NULL;
	while (fd->read(&line,"\n")>0) {
		
		// trim whitespace
		charstring::bothTrim(line);

		// parse the line (skipping blank lines and comments)
		if (line[0] && line[0]!='#') {
			parseUrl(line);
		}

		// clean up
		delete[] line;

		// break if we found the id we were looking for
		if (foundspecifiedinstance) {
			break;
		}
	}
}

void sqlrconfig_xmldom::getEnabledIds(const char *urlname,
					linkedlist< char * > *idlist) {
	debugFunction();

	debugPrintf("urlname=\"%s\"\n",urlname);

	// sanity check
	if (charstring::isNullOrEmpty(urlname)) {
		return;
	}

	// re-init
	clear();
	init();

	// set some variables
	getenabledids=true;
	this->idlist=idlist;
	foundspecifiedinstance=false;
	done=false;

	// parse the url
	parseUrl(urlname);
}

bool sqlrconfig_xmldom::accessible() {
	debugFunction();
	// FIXME: implement this
	return true;
}


extern "C" {
	SQLRUTIL_DLLSPEC sqlrconfig *new_sqlrconfig_xmldom() {
		return new sqlrconfig_xmldom();
	}
}