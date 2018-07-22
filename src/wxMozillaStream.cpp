/*
 * wxMozilla Stream
 *
 * Developers:
 *  Jeremiah Cornelius McCarthy <jeremiah@whoop-ass.ca>
 *  Kevin Ollivier <kevino@tulane.edu>
 *  Dave Fancella <david.fancella@attbi.com>

 */

NS_IMPL_ISUPPORTS(wxMozillaStream, nsIInputStream)

/**
 * Initializes mozilla stream class
 *
 * @return
 *  New instance of class	
 */
wxMozillaStream::wxMozillaStream()
{
	NS_INIT_REFCNT();
}

/**
 * Destroys class
 *
 * @return
 * 	Nothing
 */
wxMozillaStream::~wxMozillaStream()
{
}

/**
 * OpenStream
 *
 * Description:
 *
 * Returns:
 *
 */
NS_METHOD wxMozillaStream::OpenStream(const char *URI, const char *ContentType)
{
	NS_ENSURE_ARG_POINTER(URI);
	NS_ENSURE_ARG_POINTER(ContentType);

	
}

/**
 * Appends data to an opened stream
 *
 * @return
 *	Status
 */
NS_METHOD wxMozillaStream::AppendToStream(const char *Data, gint32 Len)
{
}

/**
 * Closes an opened stream
 *
 * @return
 *  NS_ERROR_FAILURE
 *  NS_OK
 */
NS_METHOD wxMozillaStream::CloseStream()
{
}

/**
 * Append some data to the stream
 *
 * @param Data
 * 	Data to be appended
 * @param Len
 * 	Length of the data to be appended
 *
 * @return
 *	Netscape status
 */
NS_METHOD wxMozillaStream::Append(const char *Data, PRUint32 Len)
{
}

/**
 * Checks for the availability of data
 *
 * @param _retval
 * 	Data
 *
 * @return
 *	Netscape status
 */
NS_IMETHODIMP wxMozillaStream::Available(PRUint32 *_retval)
{
}

/**
 * Read data from the stream
 *
 * @param Buff
 * 	Buffer to capture data from stream
 * @param Count
 * 	Maximum size of data to capture
 * @param _retval
 * 
 * @return
 *	Netscape status
 */
NS_IMETHODIMP wxMozillaStream::Read(char *Buff, PRUint32 Count, PRUint32 *_retval)
{
}

/**
 * Close stream
 *
 * @return
 *	Netscape status
 */
NS_IMETHODIMP wxMozillaStream::Close()
{
}

/**
 * Read segments
 *
 * @param Write
 * @param Closure
 * @param Count
 * @param _retval
 *
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaStream::ReadSegments(nsWriteSegmentFun Writer, void *Closure, PRUint32 Count, PRUint32 *_retval)
{
}

/**
 * Get non-blocking
 *
 * @param NonBlocking
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaStream::GetNonBlocking(PRBool *NonBlocking)
{
}

/**
 * Get observer
 *
 * @param Observer
 * 	Pointer to <code>nsIInputStreamObserver</code> class
 *
 * @return
 *	Netscape status
 */
NS_IMETHODIMP wxMozillaStream::GetObserver(nsIInputStreamObserver *Observer)
{
}

/**
 * Set observer
 *
 * @param Observer
 * 	Pointer to <code>nsIInputStreamObserver</code> class
 *
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaStream::SetObserver(nsIInputStreamObserver *Observer)
{
}
