# 引用一些库
from bs4 import BeautifulSoup
import re
import sqlite3
import xlwt
import urllib.request
import urllib.error

from xlwt.Workbook import Workbook


def main():
    baseurl = "https://movie.douban.com/top250?start="
    datalist = getData(baseurl)

    savepath = r"D:\课程文件\vs-code\python\spider\豆瓣电影.xls"
    # datalist = []
    saveData(savepath, datalist)


findLink = re.compile(r'<a href="(.*?)">')
findTitle = re.compile(r'<span class="title">(.*?)</span>')


def askUrl(url):
    head = {
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/93.0.4577.82 Safari/537.36"
    }
    request = urllib.request.Request(url, headers=head)
    html = ""
    try:
        response = urllib.request.urlopen(request)
        html = response.read().decode("utf-8")
        # print(html)
    except urllib.error.URLError as e:
        print(e)

    return html


def getData(baseurl):
    datalist = []
    for i in range(10):
        html = askUrl(baseurl + str(i*25))
        # print(html)
        soup = BeautifulSoup(html, "html.parser")
        for item in soup.find_all("div", class_="item"):
            # print(item)
            item = str(item)
            link = re.findall(findLink, item)
            title = re.findall(findTitle, item)[0]
            # print(title, ":", link[0])
            datalist.append([title, link])

    print(datalist)
    return datalist


def saveData(savepath, datalist):
    # 创建workBook对象
    book = xlwt.Workbook(encoding='utf-8')
    sheet = book.add_sheet("sheet1", cell_overwrite_ok=True)
    col = ["名称", "链接"]
    for i in range(len(col)):
        sheet.write(0, i, col[i])
    for i in range(0, len(datalist)):
        sheet.write(i+1, 0, datalist[i][0])
        sheet.write(i+1, 1, datalist[i][1])
    # book.save(r"D:\课程文件\vs-code\python\spider\123.xls")
    book.save(savepath)
    print("保存成功")


if __name__ == "__main__":
    main()
