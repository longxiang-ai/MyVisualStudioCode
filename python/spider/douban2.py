
import requests
import json
if __name__ == "__main__":
    headers = {
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/93.0.4577.82 Safari/537.36"
    }
    url = "https://movie.douban.com/j/chart/top_list"
    param = {
        "type": "17",
        "interval_id": "100:90",
        "action": "",
        "start": "0",
        "limit": "20"
    }
    response = requests.get(url=url, headers=headers, params=param)
    page_text = response.json()
    print(page_text)
    fileName = r'D:/课程文件/vs-code/python/spider/'+"豆瓣"+'.json'
    fp = open(fileName, 'w', encoding='utf-8')
    data_list = json.dump(page_text, fp=fp, ensure_ascii=False)
    print()

    print("over!!")
