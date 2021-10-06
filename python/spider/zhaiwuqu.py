# 引用一些库
from bs4 import BeautifulSoup
import re
import sqlite3
import xlwt
import urllib.request
import urllib.error

from xlwt.Workbook import Workbook


def main():
    # baseurl = r"https://www.bilibili.com/v/dance/otaku/?spm_id_from=333.5.b_64616e63655f6f74616b75.2#/all/click/0/1/2021-09-15,2021-09-16"
    baseurl = r"https://api.bilibili.com/x/web-interface/ranking/region?jsonp=jsonp&rid=20&day=7&original=0&callback=jsonCallback_bili_119525755159943572"
    datalist = getData(baseurl)

    # savepath = r"D:\课程文件\vs-code\python\spider\宅舞.xls"
    # datalist = []
    # saveData(savepath, datalist)


findLink = re.compile(r'<a href="(.*?)"')
# title="柯南广播操" class="title">柯南广播操</a>
# findTitle = re.compile(r'title="(.*?)" class="title">')
findTitle = re.compile(r'title="(.*?)"')

def askUrl(url):
    head = {
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/93.0.4577.82 Safari/537.36","cookie":"buvid3=352004C8-0EF6-4D28-946C-E231503BDE1653913infoc; LIVE_BUVID=AUTO4515859742424281; rpdid=|(J~R)mY|~YR0J'ul)lm~RkRR; CURRENT_FNVAL=80; blackside_state=1; buivd_fp=352004C8-0EF6-4D28-946C-E231503BDE1653913infoc; buvid_fp=352004C8-0EF6-4D28-946C-E231503BDE1653913infoc; DedeUserID=4876103; DedeUserID__ckMd5=0fd52f869fc28a6b; SESSDATA=34d1e4ad,1632703318,a8eb6*31; bili_jct=cf86c54f734e7a0aebe5f3746873bd6b; _uuid=20E2E7D5-A5E1-7266-57D9-A6921DDBD86647226infoc; buvid_fp_plain=352004C8-0EF6-4D28-946C-E231503BDE1653913infoc; sid=byf1hf0p; CURRENT_QUALITY=116; CURRENT_BLACKGAP=1; PVID=1; fingerprint3=c75877727360a3d1ccdf7571adfde1c1; fingerprint=c9501aeafbe97f201dae1cbdf291fcb1; fingerprint_s=17d9e76f4bea3397004f1f423bff2b98; bp_t_offset_4876103=572785999760271253; Hm_lvt_8a6e55dbd2870f0f5bc9194cddf32a02=1632223198; bp_video_offset_4876103=572940055944437400; innersign=0"
    }
    request = urllib.request.Request(url, headers=head)
    html = ""
    try:
        response = urllib.request.urlopen(request)
        html = response.read().decode("utf-8")
        print(html)
    except urllib.error.URLError as e:
        print(e)

    return html


def getData(baseurl):
    datalist = []
    for i in range(1):
        # html = askUrl(baseurl + str(i))
        html = askUrl(baseurl)
        # print(html)
        soup = BeautifulSoup(html, "html.parser")
        for item in soup.find_all("a"):
            print(item)
            item = str(item)
            link = re.findall(findLink, item)
            title = re.findall(findTitle, item)
            print(title, ":", link)
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
