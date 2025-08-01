# 🚀 Short-It

**Short-It** is a fast and minimalist RESTful URL shortener API, written in modern C++ using the Crow web framework and SQLite. It allows you to shorten long URLs, restore original URLs using short codes, and secure API routes with API key authentication.

[![Watch Demo Video](https://img.shields.io/badge/Watch-Demo-blue)](https://project-video-showcase.vercel.app/player.html?video=URL%20SHORTNER.mp4)

---

## ✨ Features

- 🔗 Shorten URLs via a simple REST API  
- 🔄 Restore original URLs from short codes  
- 🔐 API key authentication protects sensitive endpoints  
- 💾 Persistent storage using SQLite database  
- ⚡ Written with modern C++ and Crow for high performance  
- 🧹 Clean, modular RESTful design  

---

## 📚 API Endpoints

| 🌐 Route              | 🗂️ Method | 📄 Description                             | 🔒 Auth Required |
|-----------------------|-----------|----------------------------------------------|:----------------:|
| `/`                   | GET       | Public welcome/info endpoint                  | ❌ No            |
| `/api/`               | GET       | Validate API key                              | ✅ Yes           |
| `/api/short/<url>`    | GET       | Shorten a URL and return its short code       | ✅ Yes           |
| `/api/full/<short>`   | GET       | Retrieve original URL from a short code       | ✅ Yes           |

---

## ⚙️ Prerequisites

- 🏗 C++17 or newer compiler  
- 🌐 Crow Web Framework  
- 🗄 SQLite3 library and development headers  
- 🛠 CMake and Make (or any other equivalent build tools)  

---

## 🛠 Build & Run Instructions

Clone and build the project:

```
git clone https://github.com/harshsaxena213/Short-It.git
 cd Short-I
```
```
Install Crow and SQLite3 if not installed
mkdir build &  & cd build
cmake ..
Run the server (defaults to port 8080)
./shortit

```

---

## 🗃 Database Setup

Before running the server, create the SQLite database `db.sqlite` with the required tables. Open your SQLite shell and run:


```
-- Create API keys table and add your key(s)
CREATE TABLE api_keys (api_key TEXT PRIMARY KEY);
INSERT INTO api_keys VALUES ('YOUR_API_KEY_HERE');
            
-- Create URL mappings table
CREATE TABLE url (
id INTEGER PRIMARY KEY AUTOINCREMENT,
original_url TEXT NOT NULL,
shortened_url TEXT NOT NULL UNIQUE
            );

````
---


---

## 💡 Usage Examples

### 🌍 Public Route (No API Key Required)

```
GET http://localhost:8080/
```
_Response:_

```
Public Route Of Short-It Please Refer To Docs For Usage Understanding!!
```

### 🔑 Protected API Routes (Require `user-api-key` Header)

#### ✅ Validate your API Key

```
GET http://localhost:8080/api/
Headers:
user-api-key: YOUR_API_KEY_HERE

```

_Response:_

```              
Your Api Key Is Valid !
```


#### ✂️ Shorten a URL


```
GET http://localhost:8080/api/short/https://example.com
Headers:
user-api-key: YOUR_API_KEY_HERE
```

_Response:_
```
Your New Url<-->J8XOq2FRc93m2nw
```


#### 🔍 Retrieve Original URL


```
GET http://localhost:8080/api/full/J8XOq2FRc93m2nw
Headers:
user-api-key: YOUR_API_KEY_HERE

```

_Response:_

```
https://example.com
```

---

## 📁 Project Structure

- `main.cpp` — Main program entry with API routes and middleware  
- `include/api_verify.h` — API key validation logic (SQLite-based)  
- `include/short.h` — URL shortening implementation  
- `include/full.h` — URL expansion implementation  
- `db.sqlite` — SQLite database file storing API keys and URL mappings  

---

## 🏗 Design Details

- 🟢 API key authentication enforced for all `/api/` routes via Crow middleware  
- ✨ Shortened URLs use a 15-character alphanumeric code  
- 🗄 SQLite ensures persistent and durable storage  
- 🧩 Organized using Crow Blueprints for modular routing  
- 📝 Logs errors and info messages for easier debugging  

---

## 📜 License

This project is licensed under the **MIT License**.

---

## 🙌 Credits

Created by [harshsaxena213](https://github.com/harshsaxena213).

---

_For a video walkthrough and demonstration, visit:_  
[Demo Video](https://project-video-showcase.vercel.app/player.html?video=URL%20SHORTNER.mp4)
