//
// Created by 陈辉鸿 on 2024/3/11.
//

#ifndef WATCH2_HTTP_H
#define WATCH2_HTTP_H

#include <String>
#include <HTTPClient.h>

enum HTTP_METHOD
{
    POST,
    GET,
    DELETE,
    PUT
};

class Http {
public:
    HTTPClient httpClient;
    String request(const String& url, enum HTTP_METHOD method);
};


#endif //WATCH2_HTTP_H
