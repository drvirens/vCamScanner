//
//  vSysCall.cpp
//  HelloCpp
//
//  Created by Virendra Shakya on 11/2/13.
//
//

#include "vSysCall.h"



MAHandle maCreatePlaceholder() {
  //return (MAHandle) SYSCALL_THIS->resources.create_RT_PLACEHOLDER();
  MAHandle handle = 0;
  return handle;
}

int maGetDataSize(MAHandle data) {
  //Stream* b = SYSCALL_THIS->resources.get_RT_BINARY(data);
  int len = 0;
//  bool res = b->length(len);
//  DEBUG_ASSERT(res);
		//DEBUG_ASSERT(b->length(len));
  return len;
}


void maReadData(MAHandle data, void* dst, int offset, int size) {
//  SYSCALL_THIS->ValidateMemRange(dst, size);
//  Stream* b = SYSCALL_THIS->resources.get_RT_BINARY(data);
//  MYASSERT(b->seek(Seek::Start, offset), ERR_DATA_OOB);
//  MYASSERT(b->read(dst, size), ERR_DATA_OOB);
}

void maWriteData(MAHandle data, const void* src, int offset, int size) {
//  SYSCALL_THIS->ValidateMemRange(src, size);
//  Stream* b = SYSCALL_THIS->resources.get_RT_BINARY(data);
//  MYASSERT(b->seek(Seek::Start, offset), ERR_DATA_OOB);
//  MYASSERT(b->write(src, size), ERR_DATA_OOB);
}

void maDestroyObject(MAHandle handle) {
//#ifdef _android
//		// On Android, we call into the Java side to
//		// delete objects, unless it is a binary resource,
//		// which is handled in the standard way.
//  if(!SYSCALL_THIS->destroyBinaryResource(handle))
//  {
//    SYSCALL_THIS->destroyResource(handle);
//  }
//#endif
//  SYSCALL_THIS->resources.destroy(handle);
  
}

//used in downloader
int maCreateImageFromData(MAHandle placeholder, MAHandle data, int offset, int size)
{
//	MYASSERT(size>0, ERR_DATA_OOB);
//	Base::Stream* stream = Base::gSyscall->resources.get_RT_BINARY(data);
//	Surface *bitmap = 0;
//  
//	int len;
//	TEST(stream->length(len));
//  
//	if(offset<0 || offset+size>len)
//		BIG_PHAT_ERROR(ERR_DATA_OOB);
//  
//	if(!stream->ptrc()) {
//      // is not a memstream, read it to a buffer and load it.
//		MYASSERT(stream->seek(Base::Seek::Start, offset), ERR_DATA_OOB);
//		unsigned char *data = new unsigned char[size];
//		if(data==NULL) return RES_OUT_OF_MEMORY;
//		MYASSERT(stream->read(data, size), ERR_DATA_ACCESS_FAILED);
//		Base::MemStreamC memStream(data, size);
//		bitmap = Base::gSyscall->loadImage(memStream);
//		delete data;
//	} else {
//		const char *ptr = (const char*) stream->ptrc();
//		Base::MemStreamC memStream((const void*)&ptr[offset], size);
//		bitmap = Base::gSyscall->loadImage(memStream);
//	}
//  
//	if(!bitmap) return RES_BAD_INPUT;
//	if(!bitmap->image) {
//		delete bitmap;
//      // most likely bad input.
//		return RES_BAD_INPUT;
//	}
//  
//	return Base::gSyscall->resources.add_RT_IMAGE(placeholder, bitmap);

  return 0;
}

int maCreateData(MAHandle placeholder, int size) {
//#ifndef _android
//  if(size < 0) return RES_OUT_OF_MEMORY;
//  MemStream* ms = new MemStream(size);
//#else
//  char* b = SYSCALL_THIS->loadBinary(placeholder, size);
//  if(b == NULL) return RES_OUT_OF_MEMORY;
//  
//  MemStream* ms = new MemStream(b, size);
//#endif
//  if(ms == 0) return RES_OUT_OF_MEMORY;
//  if(ms->ptr()==0) { delete ms; return RES_OUT_OF_MEMORY; }
//  
//  return SYSCALL_THIS->resources.add_RT_BINARY(placeholder, ms);

  return 0;
}

void maDestroyPlaceholder(MAHandle handle) {
//		// If this is an existing dynamically allocated object,
//		// we destroy the object.
//  if (SYSCALL_THIS->resources.isDynamicResource(handle)) {
//    maDestroyObject(handle);
//  }
//  
//		// Destroy (free) the placeholder.
//  SYSCALL_THIS->resources._maDestroyPlaceholder(handle);
}


//needed for connection

MAHandle maConnect(const char* url) {
//	LOGST("Connect %i %s", gConnNextHandle, url);
//	if(gConnections.size() >= CONN_MAX)
//		return CONNERR_MAX;
//	Connection* conn;
//	if(sstrcmp(url, http_string) == 0) {
//		const char* parturl = url + sizeof(http_string) - 1;
//		TLTZ_PASS(httpCreateFinishingGetConnection(parturl, conn, false));
//    
//	} else if(sstrcmp(url, https_string) == 0) {
//		const char* parturl = url + sizeof(https_string) - 1;
//		TLTZ_PASS(httpCreateFinishingGetConnection(parturl, conn, true));
//    
//	} else if(sstrcmp(url, socket_string) == 0) {
//      //possible forms:
//      // socket://	# server on random port
//      // socket://:%i	# server on specified port
//      // socket://%s:%i	# client
//      //only the last one is allowed for now.
//    
//      //extract address and port
//		const char* parturl = url + sizeof(socket_string) - 1;
//		TLTZ_PASS(createSocketConnection(parturl, conn, Socket));
//    
//	} else if(sstrcmp(url, ssl_string) == 0) {
//		const char* parturl = url + sizeof(ssl_string) - 1;
//		TLTZ_PASS(createSocketConnection(parturl, conn, Ssl));
//    
//	} else if(sstrcmp(url, datagram_string) == 0) {
//		const char* parturl = url + sizeof(datagram_string) - 1;
//		int res;
//		TLTZ_PASS(res = createSocketConnection(parturl, conn, Datagram));
//		if(res == 2) {	// server connection
//			res = conn->connect();
//			if(res < 0) {
//				delete conn;
//				return res;
//			}
//			gConnMutex.lock();
//			{
//				MAStreamConn* mac = new MAStreamConn(gConnNextHandle, conn);
//				gConnections.insert(ConnPair(gConnNextHandle, mac));
//				mac->state = 0;
//				res = gConnNextHandle++;
//			}
//			gConnMutex.unlock();
//			return res;
//		}
//	} else if(sstrcmp(url, btspp_string) == 0) {
//      //allowed forms:
//      // btspp://localhost:%32x
//      // btspp://localhost:%32x;name=%s
//      // btspp://%12x:%i
//      //the first two are for servers, without and with service name.
//      //the last is for clients.
//    
//      //extract address and port
//		const char* parturl = url + sizeof(btspp_string) - 1;
//		const char* first_colon = strchr(parturl, ':');
//		if(!first_colon) {
//			return CONNERR_URL;
//		}
//    
//#ifndef _WIN32_WCE	//not yet supported
//		if(strstr(parturl, "localhost") == parturl) {
//        //server
//			static const char name_string[] = "name=";
//			const char* uuidStr = first_colon + 1;
//			const char* semicolon = strchr(uuidStr, ';');
//			const char* name;
//			int uuidLen;
//			if(semicolon == NULL) {
//				uuidLen = strlen(uuidStr);
//				name = NULL;
//			} else {
//				uuidLen = semicolon - uuidStr;
//        
//				const char* paramPtr = semicolon + 1;
//				if(strstr(paramPtr, name_string) == paramPtr) {
//            //we have a name
//					name = paramPtr + sizeof(name_string) - 1;
//				} else {
//					name = NULL;
//				}
//			}
//			if(uuidLen != 32)
//				return CONNERR_URL;
//			MAUUID uuid;
//        //todo, optional: check that every uuid char isxdigit().
//			if(4 != sscanf(uuidStr, "%8x%8x%8x%8x",
//                     &uuid.i[0], &uuid.i[1], &uuid.i[2], &uuid.i[3]))
//			{
//				return CONNERR_URL;
//			}
//      
//        //we have the data. let's create the server
//			BtSppServer* serv = new BtSppServer;
//			int res = serv->open(uuid, name);
//			if(res < 0) {
//				delete serv;
//				return res;
//			}
//			gConnMutex.lock();
//			{
//				MAServerConn* mac = new MAServerConn(gConnNextHandle, serv);
//				gConnections.insert(ConnPair(gConnNextHandle, mac));
//				mac->state = 0;
//				res = gConnNextHandle++;
//			}
//			gConnMutex.unlock();
//			return res;
//		} else
//#endif	//_WIN32_WCE
//		{
//        //client
//      
//			int purlLen = first_colon - parturl;
//			if(purlLen != 12) {
//				return CONNERR_URL;
//			}
//			int ai[6];	//address ints
//			if(6 != sscanf(parturl, "%2x%2x%2x%2x%2x%2x",
//                     &ai[0], &ai[1], &ai[2], &ai[3], &ai[4], &ai[5]))
//			{
//				return CONNERR_URL;
//			}
//			MABtAddr address;
//			for(int i=0; i<BTADDR_LEN; i++) {
//				address.a[i] = (byte)ai[i];
//			}
//      
//			int port = atoi(first_colon + 1);
//			if(port <= 0 || port > 30) {
//				return CONNERR_URL;
//			}
//      
//			conn = createBtSppConnection(&address, port);
//		}
//	} else {
//		return CONNERR_URL;
//	}
//    //success. let's store our new connection.
//	int result;
//	gConnMutex.lock();
//	{
//		MAStreamConn* mac = new MAStreamConn(gConnNextHandle, conn);
//		gConnections.insert(ConnPair(gConnNextHandle, mac));
//		mac->state = CONNOP_CONNECT;
//		gThreadPool.execute(new Connect(*mac));
//		result = gConnNextHandle++;
//	}
//	gConnMutex.unlock();
//	return result;

  return CONNERR_URL;
}

void maConnClose(MAHandle conn) {
//	LOGST("ConnClose %i", conn);
//	MAConn& mac = getConn(conn);
//	mac.close();	//may take too long
//	delete &mac;
//	gConnMutex.lock();
//	{
//		size_t result = gConnections.erase(conn);
//		DEBUG_ASSERT(result == 1);
//	}
//	gConnMutex.unlock();
}

//int Base::maAccept(MAHandle conn) {
//	LOGST("Accept %i", conn);
//	MAConn& mac = getConn(conn);
//	MYASSERT(mac.type == eServerConn, ERR_CONN_NOT_SERVER);
//#ifdef _WIN32_WCE
//	DEBIG_PHAT_ERROR;
//#else
//	MAServerConn& masc((MAServerConn&)mac);
//	MYASSERT((mac.state & CONNOP_ACCEPT) == 0, ERR_CONN_ALREADY_ACCEPTING);
//	mac.state |= CONNOP_ACCEPT;
//	gThreadPool.execute(new Accept(masc));
//#endif	//_WIN32_WCE
//	return 0;
//}

int maConnGetAddr(MAHandle conn, MAConnAddr* addr) {
//	LOGST("ConnGetAddr %i", conn);
//	if(conn == HANDLE_LOCAL) {
//		if(addr->family == CONN_FAMILY_BT) {
//			return Bluetooth::getLocalAddress(addr->bt.addr);
//		}
//		return CONNERR_INTERNAL;
//	}
//	MAConn& mac = getConn(conn);
//	return mac.clo->getAddr(*addr);
}

void maConnRead(MAHandle conn, void* dst, int size) {
//	LOGST("ConnRead %i %i", conn, size);
//	SYSCALL_THIS->ValidateMemRange(dst, size);
//	MAStreamConn& mac = getStreamConn(conn);
//	MYASSERT((mac.state & CONNOP_READ) == 0, ERR_CONN_ALREADY_READING);
//	mac.state |= CONNOP_READ;
//	gThreadPool.execute(new ConnRead(mac, dst, size));
}

void maConnReadFrom(MAHandle conn, void* dst, int size, MAConnAddr* src) {
//	LOGST("ConnReadFrom %i %i", conn, size);
//	SYSCALL_THIS->ValidateMemRange(dst, size);
//	MAStreamConn& mac = getStreamConn(conn);
//	MYASSERT((mac.state & CONNOP_READ) == 0, ERR_CONN_ALREADY_READING);
//	mac.state |= CONNOP_READ;
//	gThreadPool.execute(new ConnReadFrom(mac, dst, size, src));
}

void maConnWrite(MAHandle conn, const void* src, int size) {
//	LOGST("ConnWrite %i %i", conn, size);
//	SYSCALL_THIS->ValidateMemRange(src, size);
//	MAStreamConn& mac = getStreamConn(conn);
//	MYASSERT((mac.state & CONNOP_WRITE) == 0, ERR_CONN_ALREADY_WRITING);
//	mac.state |= CONNOP_WRITE;
//	gThreadPool.execute(new ConnWrite(mac, src, size));
}

void maConnWriteTo(MAHandle conn, const void* src, int size, const MAConnAddr* dst) {
//	LOGST("ConnWriteTo %i %i", conn, size);
//	SYSCALL_THIS->ValidateMemRange(src, size);
//	MAStreamConn& mac = getStreamConn(conn);
//	MYASSERT((mac.state & CONNOP_WRITE) == 0, ERR_CONN_ALREADY_WRITING);
//	mac.state |= CONNOP_WRITE;
//	gThreadPool.execute(new ConnWriteTo(mac, src, size, *dst));
}

void maConnReadToData(MAHandle conn, MAHandle data, int offset, int size) {
//	LOGST("ConnReadToData %i %i %i %i", conn, data, offset, size);
//	MYASSERT(offset >= 0, ERR_DATA_OOB);
//	MYASSERT(size > 0, ERR_DATA_OOB);
//	MYASSERT(offset + size > 0, ERR_DATA_OOB);
//  
//	MAStreamConn& mac = getStreamConn(conn);
//	MYASSERT((mac.state & CONNOP_READ) == 0, ERR_CONN_ALREADY_READING);
//  
//	Stream& stream = *SYSCALL_THIS->resources.extract_RT_BINARY(data);
//	MYASSERT(stream.ptr() != NULL, ERR_DATA_READ_ONLY);
//	{
//		int sLength;
//		MYASSERT(stream.length(sLength), ERR_DATA_OOB);
//		MYASSERT(sLength >= offset + size, ERR_DATA_OOB);
//		ROOM(SYSCALL_THIS->resources.add_RT_FLUX(data, (void*)(size_t)sLength));
//	}
//  
//	mac.state |= CONNOP_READ;
//	gThreadPool.execute(new ConnReadToData(mac, (MemStream&)stream, data, offset, size));
}

void maConnWriteFromData(MAHandle conn, MAHandle data, int offset, int size) {
//	LOGST("ConnWriteFromData %i %i %i %i", conn, data, offset, size);
//	MYASSERT(offset >= 0, ERR_DATA_OOB);
//	MYASSERT(size > 0, ERR_DATA_OOB);
//	MYASSERT(offset + size > 0, ERR_DATA_OOB);
//  
//	MAStreamConn& mac = getStreamConn(conn);
//	MYASSERT((mac.state & CONNOP_WRITE) == 0, ERR_CONN_ALREADY_WRITING);
//  
//	Stream& stream = *SYSCALL_THIS->resources.extract_RT_BINARY(data);
//	{
//		int sLength;
//		MYASSERT(stream.length(sLength), ERR_DATA_OOB);
//		MYASSERT(sLength >= offset + size, ERR_DATA_OOB);
//		ROOM(SYSCALL_THIS->resources.add_RT_FLUX(data, (void*)(size_t)sLength));
//	}
//  
//	mac.state |= CONNOP_WRITE;
//	gThreadPool.execute(new ConnWriteFromData(mac, stream, data, offset, size));
}

MAHandle maHttpCreate(const char* url, int method) {
//	LOGST("HttpCreate %i %s", gConnNextHandle, url);
//	if(gConnections.size() >= CONN_MAX)
//		return CONNERR_MAX;
//	HttpConnection* conn;
//	if(sstrcmp(url, http_string) == 0) {
//		const char* parturl = url + sizeof(http_string) - 1;
//		TLTZ_PASS(httpCreateConnection(parturl, conn, method, false));
//	} else if(sstrcmp(url, https_string) == 0) {
//		const char* parturl = url + sizeof(https_string) - 1;
//		TLTZ_PASS(httpCreateConnection(parturl, conn, method, true));
//	} else {
//		return CONNERR_URL;
//	}
//	MAConn* mac = new MAStreamConn(gConnNextHandle, conn);
//	gConnections.insert(ConnPair(gConnNextHandle, mac));
//	return gConnNextHandle++;
}

void maHttpSetRequestHeader(MAHandle conn, const char* key, const char* value) {
//	LOGS("HttpSetRequestHeader %i %s: %s\n", conn, key, value);
//	MAStreamConn& mac = getStreamConn(conn);
//	HttpConnection* http = mac.conn->http();
//	MYASSERT(http != NULL, ERR_CONN_NOT_HTTP);
//	MYASSERT(http->mState == HttpConnection::SETUP, ERR_HTTP_NOT_SETUP);
//	http->SetRequestHeader(key, value);
}

int maHttpGetResponseHeader(MAHandle conn, const char* key, char* buffer, int bufSize) {
//	SYSCALL_THIS->ValidateMemRange(buffer, bufSize);
//	MAStreamConn& mac = getStreamConn(conn);
//	HttpConnection* http = mac.conn->http();
//	MYASSERT(http != NULL, ERR_CONN_NOT_HTTP);
//	MYASSERT(http->mState == HttpConnection::FINISHED, ERR_HTTP_NOT_FINISHED);
//  
//	const std::string* valueP = http->GetResponseHeader(key);
//	if(valueP == NULL)
//		return CONNERR_NOHEADER;
//  
//	if(bufSize > (int)valueP->length()) {
//		memcpy(buffer, valueP->c_str(), valueP->length() + 1);
//	}
//  
//	return valueP->length();
}

void maHttpFinish(MAHandle conn) {
//	MAStreamConn& mac = getStreamConn(conn);
//	MYASSERT(mac.state == 0, ERR_CONN_ACTIVE);
//	HttpConnection* http = mac.conn->http();
//	MYASSERT(http != NULL, ERR_CONN_NOT_HTTP);
//	MYASSERT(http->mState == HttpConnection::SETUP || http->mState == HttpConnection::WRITING,
//           ERR_HTTP_ALREADY_FINISHED);
//	mac.state = CONNOP_FINISH;
//	http->mState = HttpConnection::FINISHING;
//	gThreadPool.execute(new HttpFinish(mac, *http));
}


