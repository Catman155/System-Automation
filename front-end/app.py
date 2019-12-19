from system_automation import app
from data_socket import start_data_socket_thread


if __name__ == '__main__':
    start_data_socket_thread()
    app.run(host="0.0.0.0", threaded=True, port=5000, use_reloader=False)

