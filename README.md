# CE4013

Team: Lye Jian Wen, Thomas Stephen Felix

## Compiling and Running Executables

### Client.exe
1. Go to /client directory
2. On Windows, run `g++ client_main.cpp proxy.cpp booking.cpp client_comms.cpp monitor.cpp query.cpp response_handler.cpp ../utilities/daytime.cpp -o Client.exe -lws2_32 -lwsock32`.
3. On Unix, run `make` to execute makefile.
4. Execute with `.\Client [SERVER_ADDRESS] [PORT] [TIMEOUT_IN_MS] [(Optional) FAILURE_RATE_DECIMAL]`. See report for details.

### server.exe
1. Go to /server directory.
2. On Windows, run `g++ main.cpp -o server udpServer.cpp daytime.cpp facility.cpp booking.cpp commHandler.cpp facilityManager.cpp utils.cpp monitor.cpp -lwsock32`.
3. On Unix, run `make` to execute makefile.
4. Execute with `.\server.exe [PORT] [INVOCATION] [FAILURE_RATE]`. See report for details.
