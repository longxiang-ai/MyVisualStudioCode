import requests
if __name__ == "__main__":
    headers = {
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/93.0.4577.82 Safari/537.36"
    }
    url = "https://www.sogou.com/web"
    keywords = "龙翔"
    param = {
        "query": keywords
    }
    response = requests.get(url=url, headers=headers, params=param)

    page_text = response.text
    print(page_text)
    fileName = r'D:/课程文件/vs-code/python/spider/'+keywords+'.html'
    with open(fileName, 'w', encoding='utf-8') as fp:
        fp.write(page_text)

    print("over!!")
