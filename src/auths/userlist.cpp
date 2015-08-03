// Copyright (c) 2014-2015  David Muse
// See the file COPYING for more information

#include <sqlrelay/sqlrserver.h>
#include <rudiments/charstring.h>

class SQLRSERVER_DLLSPEC userlist : public sqlrauth {
	public:
			userlist(xmldomnode *parameters,
					sqlrpwdencs *sqlrpe);
		bool	authenticate(sqlrserverconnection *sqlrcon,
					const char *user, const char *password);
	private:
		const char	**users;
		const char	**passwords;
		const char	**passwordencryptions;
		uint64_t	usercount;
};

userlist::userlist(xmldomnode *parameters,
				sqlrpwdencs *sqlrpe) :
				sqlrauth(parameters,sqlrpe) {

	users=NULL;
	passwords=NULL;
	passwordencryptions=NULL;
	usercount=parameters->getChildCount();
	if (!usercount) {
		return;
	}

	// create an array of users and passwords and store the
	// users and passwords from the config file in them
	// this is faster than running through the xml over and over
	users=new const char *[usercount];
	passwords=new const char *[usercount];
	passwordencryptions=new const char *[usercount];

	xmldomnode *user=parameters->getFirstTagChild("user");
	for (uint64_t i=0; i<usercount; i++) {

		users[i]=user->getAttributeValue("user");
		passwords[i]=user->getAttributeValue("password");

		// support modern "passwordencryptionid" and fall back to
		// older "passwordencryption" attribute
		const char	*pwdencid=
				user->getAttributeValue("passwordencryptionid");
		if (!pwdencid) {
			pwdencid=user->getAttributeValue("passwordencryption");
		}
		passwordencryptions[i]=pwdencid;

		user=user->getNextTagSibling("user");
	}
}

bool userlist::authenticate(sqlrserverconnection *sqlrcon,
				const char *user, const char *password) {

	// run through the user/password arrays...
	for (uint32_t i=0; i<usercount; i++) {

		// if the user matches...
		if (!charstring::compare(user,users[i])) {

			if (sqlrpe &&
				charstring::length(passwordencryptions[i])) {

				// if password encryption is being used...

				// get the module
				sqlrpwdenc	*pe=
					sqlrpe->getPasswordEncryptionById(
							passwordencryptions[i]);
				if (!pe) {
					return false;
				}

				// For one-way encryption, encrypt the password
				// that was passed in and compare it to the
				// encrypted password in the config file.
				// For two-way encryption, decrypt the password
				// from the config file and compare ot to the
				// password that was passed in...

				bool	retval=false;
				char	*pwd=NULL;
				if (pe->oneWay()) {

					// encrypt the password
					// that was passed in
					pwd=pe->encrypt(password);

					// compare it to the encrypted
					// password from the config file
					retval=!charstring::compare(
							pwd,passwords[i]);

				} else {

					// decrypt the password
					// from the config file
					pwd=pe->decrypt(passwords[i]);

					// compare it to the password
					// that was passed in
					retval=!charstring::compare(
							password,pwd);
				}

				// clean up
				delete[] pwd;

				// return true/false
				return retval;

			} else {

				// if password encryption isn't being used,
				// return true if the passwords match
				return !charstring::compare(password,
								passwords[i]);
			}
		}
	}
	return false;
}

extern "C" {
	SQLRSERVER_DLLSPEC sqlrauth *new_sqlrauth_userlist(
						xmldomnode *users,
						sqlrpwdencs *sqlrpe) {
		return new userlist(users,sqlrpe);
	}
}