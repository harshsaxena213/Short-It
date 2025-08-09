import requests

# Set your endpoint and data
url = "http://localhost:8081/admin/add_api_key"
headers = {
    "admin-api-key": "key9876value5432"  # Replace with a valid admin key in your db
}
data = {
    "username": "admin2",
    "email_id": "admin@admin.com",
    "description": "this is admin",
    "id": "5"
}

def test_valid_add_api_key():
    response = requests.post(url, headers=headers, data=data)
    print("Status code:", response.status_code)
    print("Response text:", response.text)
    assert response.status_code == 200, "Should return 200 OK"
    assert len(response.text.strip()) == 15, "API key should be 15 chars (random string)"

def test_invalid_admin_key():
    bad_headers = {"admin-api-key": "not_a_real_admin_key"}
    response = requests.post(url, headers=bad_headers, data=data)
    print("Invalid admin key status:", response.status_code)
    print("Invalid admin key response:", response.text)
    assert response.status_code == 401, "Should return 401 for invalid admin key"

def test_missing_param():
    bad_data = data.copy()
    del bad_data["username"]
    response = requests.post(url, headers=headers, data=bad_data)
    print("Missing param status:", response.status_code)
    print("Missing param response:", response.text)
    assert response.status_code == 400, "Should return 400 for missing parameter"

if __name__ == "__main__":
    test_valid_add_api_key()
    test_invalid_admin_key()
    test_missing_param()
