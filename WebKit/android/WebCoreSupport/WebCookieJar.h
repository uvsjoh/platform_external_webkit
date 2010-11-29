/*
 * Copyright 2010, The Android Open Source Project
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef WebCookieJar_h
#define WebCookieJar_h

#include "ChromiumIncludes.h"

#include <wtf/ThreadingPrimitives.h>

namespace android {

class WebCookieJar : public net::CookiePolicy {
public:
    static WebCookieJar* get(bool isPrivateBrowsing);

    // CookiePolicy implementation from external/chromium
    virtual int CanGetCookies(const GURL& url, const GURL& first_party_for_cookies, net::CompletionCallback*);
    virtual int CanSetCookie(const GURL& url, const GURL& first_party_for_cookies, const std::string& cookie_line, net::CompletionCallback*);

    bool allowCookies();
    void setAllowCookies(bool allow);
    void cleanupFiles();

    // Instead of this it would probably be better to add the cookie methods
    // here so the rest of WebKit doesn't have to know about Chromium classes
    net::CookieStore* cookieStore() { return m_cookieStore.get(); }
    net::CookiePolicy* cookiePolicy() { return this; }

private:
    WebCookieJar(const std::string& databaseFilePath);

    scoped_refptr<net::CookieStore> m_cookieStore;
    bool m_allowCookies;
    WTF::Mutex m_allowCookiesMutex;
    std::string m_databaseFilePath;
};

}

#endif
