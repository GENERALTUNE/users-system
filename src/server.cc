
#include <iostream>
#include "server/UserSystemImpl.h"

static const char* CERT_PEM = R"cert(
-----BEGIN CERTIFICATE-----
MIICmDCCAh6gAwIBAgIJAMLiaeoJDFRqMAoGCCqGSM49BAMCMIGJMQswCQYDVQQG
EwJ6aDESMBAGA1UECAwJZ3Vhbmdkb25nMRIwEAYDVQQHDAlndWFuZ3pob3UxEDAO
BgNVBAoMB2dlcmFudGUxDTALBgNVBAsMBGtlamkxEDAOBgNVBAMMB2dlcmFudGUx
HzAdBgkqhkiG9w0BCQEWEDU3NzE3NDA0MkBxcS5jb20wHhcNMjAwMzI0MDQyMzE0
WhcNMzAwMzIyMDQyMzE0WjCBiTELMAkGA1UEBhMCemgxEjAQBgNVBAgMCWd1YW5n
ZG9uZzESMBAGA1UEBwwJZ3Vhbmd6aG91MRAwDgYDVQQKDAdnZXJhbnRlMQ0wCwYD
VQQLDARrZWppMRAwDgYDVQQDDAdnZXJhbnRlMR8wHQYJKoZIhvcNAQkBFhA1Nzcx
NzQwNDJAcXEuY29tMHYwEAYHKoZIzj0CAQYFK4EEACIDYgAEHWdDWkaCGeT+auNx
+X9QkRqrM0KZZlKQTaG2lAydMWUDO3YsqldR8nWnXGrXR/zfGPOPSNWVCyw8vyRN
hJst88yjARKN6K/Cc0llkCwRLBgEYlxZyl3bcP37Yio8/q7co1AwTjAdBgNVHQ4E
FgQUo7XbKkQCGk2nUIAUI2PYp4NFLDkwHwYDVR0jBBgwFoAUo7XbKkQCGk2nUIAU
I2PYp4NFLDkwDAYDVR0TBAUwAwEB/zAKBggqhkjOPQQDAgNoADBlAjEAqNesAS3A
FZodsZddaeolwAc7pjeUaXN8RvjZ5W4iqzQ+RyxqLEBME0DUxUnKXO9lAjAlEcoP
SecfH3e1D+VnlZnngRz/mjgo38VeNUf9OhWL0jwnmoma5mdWxMgk7vhi7pc=
-----END CERTIFICATE-----
)cert";

static const char* KEY_PEM = R"key(
-----BEGIN CERTIFICATE-----
MIICmDCCAh6gAwIBAgIJAMLiaeoJDFRqMAoGCCqGSM49BAMCMIGJMQswCQYDVQQG
EwJ6aDESMBAGA1UECAwJZ3Vhbmdkb25nMRIwEAYDVQQHDAlndWFuZ3pob3UxEDAO
BgNVBAoMB2dlcmFudGUxDTALBgNVBAsMBGtlamkxEDAOBgNVBAMMB2dlcmFudGUx
HzAdBgkqhkiG9w0BCQEWEDU3NzE3NDA0MkBxcS5jb20wHhcNMjAwMzI0MDQyMzE0
WhcNMzAwMzIyMDQyMzE0WjCBiTELMAkGA1UEBhMCemgxEjAQBgNVBAgMCWd1YW5n
ZG9uZzESMBAGA1UEBwwJZ3Vhbmd6aG91MRAwDgYDVQQKDAdnZXJhbnRlMQ0wCwYD
VQQLDARrZWppMRAwDgYDVQQDDAdnZXJhbnRlMR8wHQYJKoZIhvcNAQkBFhA1Nzcx
NzQwNDJAcXEuY29tMHYwEAYHKoZIzj0CAQYFK4EEACIDYgAEHWdDWkaCGeT+auNx
+X9QkRqrM0KZZlKQTaG2lAydMWUDO3YsqldR8nWnXGrXR/zfGPOPSNWVCyw8vyRN
hJst88yjARKN6K/Cc0llkCwRLBgEYlxZyl3bcP37Yio8/q7co1AwTjAdBgNVHQ4E
FgQUo7XbKkQCGk2nUIAUI2PYp4NFLDkwHwYDVR0jBBgwFoAUo7XbKkQCGk2nUIAU
I2PYp4NFLDkwDAYDVR0TBAUwAwEB/zAKBggqhkjOPQQDAgNoADBlAjEAqNesAS3A
FZodsZddaeolwAc7pjeUaXN8RvjZ5W4iqzQ+RyxqLEBME0DUxUnKXO9lAjAlEcoP
SecfH3e1D+VnlZnngRz/mjgo38VeNUf9OhWL0jwnmoma5mdWxMgk7vhi7pc=
-----END CERTIFICATE-----
)key";

constexpr auto DEFAULT_DB_URL = "mysqlx://root:106.14.56.249:33060@gerante";

void RunServer(bool enableSsl, std::string& dbUrl)
{
    std::string server_address("0.0.0.0:3389");
    UserSystemImpl service(dbUrl);

    grpc::SslServerCredentialsOptions::PemKeyCertPair pemKeyCertPair;
    pemKeyCertPair.private_key = std::string(KEY_PEM);
    pemKeyCertPair.cert_chain = std::string(CERT_PEM);
    grpc::SslServerCredentialsOptions credentialsOptions;
    credentialsOptions.pem_root_certs = "";
    credentialsOptions.pem_key_cert_pairs.emplace_back(pemKeyCertPair);

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, enableSsl ?
                                             grpc::SslServerCredentials(credentialsOptions) :
                                             grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    std::cout << "Use db url " << dbUrl << std::endl;

    server->Wait();
}

static void ShowUsage()
{
    std::cout << "Simple user system application\n"
              << "Usage:\n"
              << "\tserver [OPTION...]\n\n"
              << "Help Options:\n"
              << "\t-h, --help\tShow this help\n\n"
              << "Application Options:\n"
              << "\t--enable-ssl\tUse ssl certificate, DO NOT support connect from IP address\n"
              << "\t--db-url\tDatabase url connect information, e.g mysqlx://root:password@db_host\n"
              << std::endl;
    std::exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[])
{
    if (argc == 2 && (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help")) {
        ShowUsage();
    }

    // ssl server didn't support connect from IP address
    bool sslSupport = false;
    std::string dbUrl(DEFAULT_DB_URL);
    for (int i = 0; i < argc; i++) {
        if (std::string(argv[i]) == "--enable-ssl") {
            sslSupport = true;
        }

        if (std::string(argv[i]) == "--db-url" && (i+1) < argc) {
            dbUrl = std::string(argv[i+1]);
        }
    }

    RunServer(sslSupport, dbUrl);
    return EXIT_SUCCESS;
}
