import requests
import multiprocessing
import time

def worker(url):
    try:
        response = requests.get(url)
        print("Concurrent Request Response:", response.status_code)
    except requests.RequestException as e:
        print("Concurrent Request Failed:", e)
        sys.exit(1)

def test_get():
    url = "http://localhost:8080/"
    try:
        response = requests.get(url)
        # print("GET Response:", response.status_code, response.text)
    except requests.RequestException as e:
        print("GET Request Failed:", e)
        sys.exit(1)

def test_post():
    url = "http://localhost:8080/upload"
    data = {"name": "test", "message": "Hello Webserv!"}
    try:
        response = requests.post(url, data=data)
        # print("POST Response:", response.status_code, response.text)
    except requests.RequestException as e:
        print("POST Request Failed:", e)
        sys.exit(1)

def test_delete():
    url = "http://localhost:8080/delete_test"
    try:
        response = requests.delete(url)
        # print("DELETE Response:", response.status_code, response.text)
    except requests.RequestException as e:
        print("DELETE Request Failed:", e)
        sys.exit(1)

def test_headers():
    url = "http://localhost:8080/"
    headers = {"User-Agent": "WebservTester", "Accept": "application/json"}
    try:
        response = requests.get(url, headers=headers)
        # print("Headers Test Response:", response.status_code, response.headers)
    except requests.RequestException as e:
        print("Headers Test Failed:", e)
        sys.exit(1)

def test_cgi():
    url = "http://localhost:8080/cgi/shape.py"
    try:
        response = requests.get(url)
        # print("CGI Response:", response.status_code, response.text)
    except requests.RequestException as e:
        print("CGI Test Failed:", e)
        sys.exit(1)


def test_concurrent_requests():
    url = "http://localhost:8080/"  # Ensure the URL is defined
    processes = []
    for _ in range(100):  # 10 concurrent requests
        p = multiprocessing.Process(target=worker, args=(url,))  # Use url instead of URL
        processes.append(p)
        p.start()
    
    for p in processes:
        p.join()

def test_performance():
    url = "http://localhost:8080/"
    start_time = time.time()
    for _ in range(100):  # 100 requests
        try:
            requests.get(url)
        except requests.RequestException:
            pass
    end_time = time.time()
    print("Performance Test: 100 requests in", end_time - start_time, "seconds")

if __name__ == "__main__":
    test_get()
    test_post()
    test_delete()
    test_headers()
    test_cgi()
    test_concurrent_requests()
    test_performance()
