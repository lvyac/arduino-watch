//
// Created by 陈辉鸿 on 2024/3/11.
//

#include "Http.h"

String Http::request(const String& url, enum HTTP_METHOD method) {
    int code;

    httpClient.begin(url);
    switch (method)
    {
        case POST:
            code = httpClient.POST("");
            break;
        case DELETE:
            code = httpClient.sendRequest("DELETE");
            break;
        default:
            code = httpClient.GET();
    }

    String payload;
    if (code > 0)
    {
        payload = httpClient.getString();
    }

    httpClient.end();
    return payload;
}
