#ifndef __MFCMESSAGE_H__
#define __MFCMESSAGE_H__



enum
{
	NM_ADDMSG,
	NM_REMOVEMSG,

};

struct NetMessage
{
	int id;
};

#define BEGIN_MSG_MAP() \
	void ExecMessage(NetMessage* pMsg)				\
	{												\
													\
		switch (pMsg->id)							\
		{											\

#define HANDLE_MSG(message, fn)						\
			case (message) : (fn)((pMsg)); break;	\

#define END_MSG_MAP()	\
		default:		\
		break;			\
		}				\
	}					\

class MessageMgr
{
public:
	MessageMgr() {}
	~MessageMgr() {}

	//void ExecMessage(NetMessage* pMsg);

	void OnAddMsg(NetMessage* pMsg);
	void OnRemoveMsg(NetMessage* pMsg);

	BEGIN_MSG_MAP()
			HANDLE_MSG(NM_ADDMSG, OnAddMsg)
			HANDLE_MSG(NM_REMOVEMSG, OnRemoveMsg)
	END_MSG_MAP()

private:

};
#endif