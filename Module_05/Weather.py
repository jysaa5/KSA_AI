# lotto.py
# _*_ coding: utf-8 _*_
import sys
from urllib.request import urlopen
from urllib.parse import urlencode, unquote, quote_plus, quote
import urllib

from xml.etree.ElementTree import parse

import pymysql
import requests

from bs4 import BeautifulSoup


url = "http://openapi.airkorea.or.kr/openapi/services/rest/ArpltnInforInqireSvc/getCtprvnRltmMesureDnsty"

api_key = 'E8ZjiDP5QBA9z4FPo%2FMEMbbt6SpDm2vsZDiKBqyYWEorfqjJ2MhW9ZbiX6JZRGCnlMDSyKPW5uQuaxPURITsKA%3D%3D'

api_key_decode = requests.utils.unquote(api_key)

city = quote("서울")

queryParams = '?'+urlencode({quote_plus('sidoName'): city, quote_plus('pageNo'): '1', quote_plus('numOfRows'): '10', quote_plus('ServiceKey'): api_key_decode, quote_plus('ver'): '1.3'})

request = urllib.request.Request(url+unquote(queryParams)+'.xml')

print('Your Request: \n'+url+queryParams)
request.get_method = lambda: 'GET'
response_body = urlopen(request).read().decode('utf8')
print("\nResult:")
print(response_body)
print("\nDataType of Result Data:")
print(type(response_body))


rows = []

#resp = parse(response_body)

xmlsoup = BeautifulSoup(response_body, 'html.parser')
items = xmlsoup.find_all('item')
city = xmlsoup.find_all('stationName')
pm10value = xmlsoup.find_all('pm10value')

print(city)



for item1 in pm10value:
    pv = int(item1.text)
    info = pv
    #rows.append(pv)
    #print(item)
    #print(pm10value)
    print(pv)
    rows.append(info)
    #print(rows)




def insert():
    db = pymysql.connect(host="192.168.187.74", user="lotto", passwd="edu.123", db="lotto")
    cursor = db.cursor()

    for dic in rows:
        pValue = dic
        insertData = pValue
        sql = """INSERT INTO Weather(`pm10Value`) VALUES("%d")""" %insertData

        try:
             cursor.execute(sql)
             db.commit()

        except:
            #print(sys.exc_info()[0])
             print(sys.exc_info())
             db.rollback()

         #cursor.close()
         #db.close()

    cursor.close()
    db.close()


# def crawler():
#     for i in range(1, 10):
#         crawler_url = basic_url + str(i)
#         print("crawler: " + crawler_url)
#         resp = requests.get(crawler_url)
#         soup = BeautifulSoup(resp.text, "lxml")
#
#         line = str(soup.find("items"))
#         #line = str(soup.find("response", {"body": "items", "name": "description"})['content'])
#         print(line)
#         # folder4 > div.opened > div:nth-child(2) > span:nth-child(2)
#         #begin = line.find("당첨번호")
#         #begin = line.find(" ", begin) + 1
#         #end = line.find(".", begin)
#         #numbers = line[begin:end]
#         #begin = line.find("총")
#         #begin = line.find(" ", begin) + 1
#         #end = line.find("명", begin)
#         #persons = line[begin:end]
#         #begin = line.find("당첨금액")
#         #begin = line.find(" ", begin) + 1
#         #end = line.find("원", begin)
#         #amount = line[begin:end]
#         #info = {}
#         #info["회차"] = i
#         #info["번호"] = numbers
#         #info["당첨자"] = persons
#         #info["금액"] = amount
#         #lotto_list.append(info)


# def insert():
#     db = pymysql.connect(host="192.168.187.74", user="lotto", passwd="edu.123", db="lotto")
#     cursor = db.cursor()
#
#     for dic in lotto_list:
#         count = dic["회차"]
#         numbers = dic["번호"]
#         persons = dic["당첨자"]
#         amounts = dic["금액"]
#
#         print(numbers)
#         print(persons)
#         print(amounts)
#         print("insert to database at" + str(count))
#
#         numberlist = str(numbers).split(",")
#
#         print(numberlist)
#         dataCount = int(count)
#         dataNum1 = int(numberlist[0])
#         dataNum2 = int(numberlist[1])
#         dataNum3 = int(numberlist[2])
#         dataNum4 = int(numberlist[3])
#         dataNum5 = int(numberlist[4])
#         dataNum6 = int(numberlist[5].split('+')[0])
#         dataNum7 = int(numberlist[5].split('+')[1])
#
#         dataPerson = int(persons)
#         dataAmount = str(amounts)
#
#         print(type(dataCount))
#         print(type(dataNum1))
#         print(type(dataNum2))
#         print(type(dataNum3))
#         print(type(dataNum4))
#         print(type(dataNum5))
#         print(type(dataNum6))
#         print(type(dataNum7))
#         print(type(dataPerson))
#         print(type(dataAmount))
#
#         print(dataNum6)
#         print(dataNum7)
#
#         insertData = (dataCount, dataNum1, dataNum2, dataNum3, dataNum4, dataNum5, dataNum6, dataNum7, dataPerson, dataAmount)
#
#         #sql = 'INSERT INTO data(count, 1, 2, 3, 4, 5, 6, 7, person, amount) VALUES({},{},{},{},{},{},{},{},{},{})'.format(dataCount, dataNum1, dataNum2, dataNum3, dataNum4, dataNum5, dataNum6, dataNum7, dataPersons, amounts)
#         sql = """INSERT INTO Data(`count`, `1`, `2`, `3`, `4`, `5`, `6`, `7`, `person`, `amount`) VALUES("%d", "%d", "%d", "%d", "%d", "%d", "%d", "%d", "%d", "%s")""" %insertData
#
#         try:
#             cursor.execute(sql)
#             db.commit()
#
#         except:
#             #print(sys.exc_info()[0])
#             print(sys.exc_info())
#             db.rollback()
#
#         #cursor.close()
#         #db.close()
#
#     cursor.close()
#     db.close()


def main():
    #crawler()
    insert()



if __name__ == "__main__":
     main()