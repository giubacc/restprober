#pragma once
#include "jsenv.h"

namespace cbox {
struct conversation;

struct request {

    request(conversation &parent);

    int reset(const std::string &raw_host,
              const Json::Value &request_in);

    int process(const std::string &raw_host,
                Json::Value &request_in,
                Json::Value &requests_out);

    int execute(const std::string &method,
                const std::optional<std::string> &auth,
                const std::string &uri,
                const std::string &query_string,
                const std::string &data,
                Json::Value &request_in,
                Json::Value &request_out);

    int on_response(const RestClient::Response &resRC,
                    const int64_t rtt,
                    Json::Value &request_in,
                    Json::Value &request_out);

    int process_response(const RestClient::Response &resRC,
                         const int64_t rtt,
                         Json::Value &response_in,
                         Json::Value &response_out);

    // ------------
    // --- HTTP ---
    // ------------

    /**
     * POST
     */
    int post(RestClient::HeaderFields &reqHF,
             const std::optional<std::string> &auth,
             const std::string &uri,
             const std::string &query_string,
             const std::string &data,
             const std::function<int(const RestClient::Response &, const int64_t)> &cb);

    /**
     * PUT
     */
    int put(RestClient::HeaderFields &reqHF,
            const std::optional<std::string> &auth,
            const std::string &uri,
            const std::string &query_string,
            const std::string &data,
            const std::function <int (const RestClient::Response &, const int64_t)> &cb);

    /**
     * GET
     */
    int get(RestClient::HeaderFields &reqHF,
            const std::optional<std::string> &auth,
            const std::string &uri,
            const std::string &query_string,
            const std::function <int (const RestClient::Response &, const int64_t)> &cb);

    /**
     * DELETE
     */
    int del(RestClient::HeaderFields &reqHF,
            const std::optional<std::string> &auth,
            const std::string &uri,
            const std::string &query_string,
            const std::function <int (const RestClient::Response &, const int64_t)> &cb);

    /**
     * HEAD
     */
    int head(RestClient::HeaderFields &reqHF,
             const std::optional<std::string> &auth,
             const std::string &uri,
             const std::string &query_string,
             const std::function <int (const RestClient::Response &, const int64_t)> &cb);

  private:

    int prepare_http_req(const char *method,
                         const std::optional<std::string> &auth,
                         const std::string &query_string,
                         const std::string &data,
                         std::string &uri_out,
                         RestClient::HeaderFields &reqHF);

    // -------------
    // --- UTILS ---
    // -------------

    void dump_hdr(const RestClient::HeaderFields &hdr) const;
    int mocked_to_res(RestClient::Response &resRC);

    // -----------
    // --- REP ---
    // -----------

    //parent
    conversation &parent_;

    //js environment
    js::js_env &js_env_;

    //event logger
    std::shared_ptr<spdlog::logger> event_log_;

    //current response mock
    Json::Value *response_mock_ = nullptr;

    //request connection
    std::unique_ptr<RestClient::Connection> conv_conn_;
};

}
