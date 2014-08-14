#ifndef MFACOMMON_H
#define MFACOMMON_H


namespace Caca
{
	//MFA means "Mesh File Access"
	enum MFAErrCode
	{
		MFA_NO_ERR,
		MFA_USER_CANCEL,
		MFA_OPEN_FAILED,
		MFA_WRITE_FAILED,
		MFA_READER_FAILED,
		MFA_UNKNOWN_ERR
	};
}

#endif
