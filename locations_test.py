

import requests

class HTTPTest:
    @staticmethod
    def test(url, expected_code, test_name="Test"):
        try:
            response = requests.get(url)
            if response.status_code == expected_code:
                print(f"OK: {test_name}")
            else:
                print(f"KO: {test_name} - Expected {expected_code}, but got {response.status_code}")
        except requests.RequestException as e:
            print(f"KO: {test_name} - Error: {e}")




HTTPTest.test("http://localhost:8080/", 200, "Test GET Request")
HTTPTest.test("http://localhost:8080/upload", 200, "Test POST Request")
HTTPTest.test("http://127.0.0.1:8080/Templ/Upload.html", 200)
HTTPTest.test("http://127.0.0.1:8080/Templ/delete_test.html", 200)

HTTPTest.test("http://localhost:8080/nonexistent", 404, "Test Nonexistent Page")


HTTPTest.test("http://127.0.0.1:8080/forbidden", 405)
HTTPTest.test("http://127.0.0.1:8080/forbidden/", 405)
HTTPTest.test("http://127.0.0.1:8080/forbidden/cdfcdc/csdcsdcsc/dcsdcds", 405)
HTTPTest.test("http://127.0.0.1:8080/forbidden/cdrrcdc/dcdsccsdcsdcsc/dcsdcsccds", 405)
HTTPTest.test("http://127.0.0.1:8080/forbidden/cdefcdc/csdcsdcsc/dcsdcds", 405)
HTTPTest.test("http://127.0.0.1:8080/forbidden/cwedweddcdc/cscdsddcsdcsc/dcdscsdcds", 405)
HTTPTest.test("http://127.0.0.1:8080/forbidden/cdcdc/csdcsddsccsc/dcscdscsdcds", 405)
HTTPTest.test("http://127.0.0.1:8080/forbidden/cdcdc/csdcdesdcscwsdcsc/dcsdcds", 405)
HTTPTest.test("http://127.0.0.1:8080/forbidden/s/sd/dcsdcds", 405)
HTTPTest.test("http://127.0.0.1:8080/forbidden/cdcdc/dsc/dcsdcds", 405)






HTTPTest.test("http://127.0.0.1:8080/cgi/big.php/env/system/configuration/settings/deeply_nested_configs?var=PATH&debug=true&extra_env_vars=%5B%22VAR1%22%2C%22VAR2%22%2C%22VAR3%22%5D", 200)
HTTPTest.test("http://127.0.0.1:8080/cgi/calc.py/compute/very/long/path/with/lots/of/numbers/12345/67890/and/letters?x=999999&y=-54321&operation=multiply&precision=high", 200)
HTTPTest.test("http://127.0.0.1:8080/cgi/cookies.py/user/data/profile/settings/preferences/theme/dark/mode/on?session=abcd1234longlongsessionstring&user=admin&permissions=%5B%22read%22%2C%22write%22%2C%22execute%22%5D", 200)
HTTPTest.test("http://127.0.0.1:8080/cgi/env.php/delete/item/inventory/stock/warehouse/section/row/column?item_id=998877665544332211&confirm=true&reason=expired", 200)
HTTPTest.test("http://127.0.0.1:8080/cgi/extrem_large.py/deeply/structured/data/endpoint/api/v2/resource/metadata?flag=true&debug=1&extra_info=%7B%22info%22%3A%22large_text_block_here%22%7D", 200)
HTTPTest.test("http://127.0.0.1:8080/cgi/name.py/api/v1/resource/data/structured/in/deeply/nested/format/json?key=value&filter=%7B%22type%22%3A%22complex%22%2C%22limit%22%3A1000%7D", 200)
HTTPTest.test("http://127.0.0.1:8080/cgi/path_info.php/calculate/stack/deeply/embedded/expressions/long_formula/special_cases?expr=3,4,+,5,*,6,-,sqrt,log,exp,sin,cos", 200)
HTTPTest.test("http://127.0.0.1:8080/cgi/search.py/triangle/area/circle/square/hexagon/complex_shape?dimensions=%7B%22triangle%22%3A%5B5%2C10%5D%2C%22circle%22%3A%2215%22%7D", 200)
HTTPTest.test("http://127.0.0.1:8080/cgi/shape.py/triangle/area/circle/square/hexagon/complex_shape?dimensions=%7B%22triangle%22%3A%5B5%2C10%5D%2C%22circle%22%3A%2215%22%7D", 200)
HTTPTest.test("http://127.0.0.1:8080/cgi/testenv.php/triangle/area/circle/square/hexagon/complex_shape?dimensions=%7B%22triangle%22%3A%5B5%2C10%5D%2C%22circle%22%3A%2215%22%7D", 200)
HTTPTest.test("http://127.0.0.1:8080/cgi/timeout.py", 504 )






