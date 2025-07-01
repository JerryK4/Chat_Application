# call_gemini.py
import sys
import os
import google.generativeai as genai

# Đặt API Key tại đây hoặc dùng biến môi trường
GEMINI_API_KEY = os.getenv("GEMINI_API_KEY") or "AIzaSyAL9SYkQ5e1PV7izDzxcpz6ghwe8hRLcVg"

if GEMINI_API_KEY.startswith("YOUR_"):
    print("[AI ERROR]: Chưa cấu hình API key Gemini.")
    sys.exit(1)

genai.configure(api_key=GEMINI_API_KEY)

prompt = sys.stdin.read().strip()

if not prompt:
    print("[AI]: Câu hỏi rỗng.")
    sys.exit(0)

try:
    model = genai.GenerativeModel("gemini-1.5-flash")
    response = model.generate_content(prompt)
    print("[AI]:", response.text)
except Exception as e:
    print("[AI ERROR]:", e)
