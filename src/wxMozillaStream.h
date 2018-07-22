#ifndef __WX_MOZILLA_STREAM_H__
#define __WX_MOZILLA_STREAM_H__
/*
 * wxMozilla Stream
 *
 * Developers:
 *  Jeremiah Cornelius McCarthy <jeremiah@whoop-ass.ca>
 *  Kevin Ollivier <kevino@tulane.edu>
 *  Dave Fancella <david.fancella@attbi.com>
 */

/**
 * Mozilla streamed data class
 */
class wxMozillaStream: public nsIInputStream
{
private:
	nsCOMPtr<nsIOutputStream> mOutputStream;
	nsCOMPtr<nsIInputStream> mInputStream;

public:

	wxMozillaStream();
	virtual ~wxMozillaStream();

	NS_METHOD OpenStream(const char *URI, const char *ContentType);
	NS_METHOD AppendToStream(const char *Data, PRInt32 Len);
	NS_METHOD CloseStream(void);

	NS_METHOD Append(const char *Data, PRUint32 Len);
	
	NS_DECL_ISUPPORTS
	NS_DECL_NSIINPUTSTREAM
};

#endif
