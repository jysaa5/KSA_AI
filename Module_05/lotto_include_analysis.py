# lotto.py

import requests
from bs4 import BeautifulSoup
import pymysql
import sys
from matplotlib import pyplot as plt
import numpy as np


# 웹 크롤링 한 결과를 저장할 리스트

lotto_list = []
basic_url = "https://dhlottery.co.kr/gameResult.do?method=byWin&drwNo="


def crawler():
    for i in range(1, 918):
        crawler_url = basic_url + str(i)
        print("crawler: " + crawler_url)

        resp = requests.get(crawler_url)
        soup = BeautifulSoup(resp.text, "lxml")
        line = str(soup.find("meta", {"id": "desc", "name": "description"})['content'])
        print(line)

        begin = line.find("당첨번호")
        begin = line.find(" ", begin) + 1
        end = line.find(".", begin)
        numbers = line[begin:end]
        begin = line.find("총")
        begin = line.find(" ", begin) + 1
        end = line.find("명", begin)
        persons = line[begin:end]
        begin = line.find("당첨금액")
        begin = line.find(" ", begin) + 1
        end = line.find("원", begin)
        amount = line[begin:end]
        info = {}
        info["회차"] = i
        info["번호"] = numbers
        info["당첨자"] = persons
        info["금액"] = amount
        lotto_list.append(info)


def insert():
    db = pymysql.connect(host="192.168.187.74", user="lotto", passwd="edu.123", db="lotto")
    cursor = db.cursor()

    for dic in lotto_list:
        count = dic["회차"]
        numbers = dic["번호"]
        persons = dic["당첨자"]
        amounts = dic["금액"]

        print(numbers)
        print(persons)
        print(amounts)
        print("insert to database at" + str(count))

        numberlist = str(numbers).split(",")

        print(numberlist)
        dataCount = int(count)
        dataNum1 = int(numberlist[0])
        dataNum2 = int(numberlist[1])
        dataNum3 = int(numberlist[2])
        dataNum4 = int(numberlist[3])
        dataNum5 = int(numberlist[4])
        dataNum6 = int(numberlist[5].split('+')[0])
        dataNum7 = int(numberlist[5].split('+')[1])

        dataPerson = int(persons)
        dataAmount = str(amounts)

        print(type(dataCount))
        print(type(dataNum1))
        print(type(dataNum2))
        print(type(dataNum3))
        print(type(dataNum4))
        print(type(dataNum5))
        print(type(dataNum6))
        print(type(dataNum7))
        print(type(dataPerson))
        print(type(dataAmount))

        print(dataNum6)
        print(dataNum7)

        insertData = (dataCount, dataNum1, dataNum2, dataNum3, dataNum4, dataNum5, dataNum6, dataNum7, dataPerson, dataAmount)

        #sql = 'INSERT INTO data(count, 1, 2, 3, 4, 5, 6, 7, person, amount) VALUES({},{},{},{},{},{},{},{},{},{})'.format(dataCount, dataNum1, dataNum2, dataNum3, dataNum4, dataNum5, dataNum6, dataNum7, dataPersons, amounts)
        sql = """INSERT INTO Data(`count`, `1`, `2`, `3`, `4`, `5`, `6`, `7`, `person`, `amount`) VALUES("%d", "%d", "%d", "%d", "%d", "%d", "%d", "%d", "%d", "%s")""" %insertData

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


def analysis():
    db = pymysql.connect(host="192.168.187.74", user="lotto", passwd="edu.123", db="lotto")
    cursor = db.cursor()

    myarray = [0 for i in range(46)]
    sql = """SELECT `1`, `2`, `3`, `4`, `5`, `6`, `7` FROM Data"""
    cursor.execute(sql)

    result = cursor.fetchall()
    cursor.close()
    db.close()
    print(result)
    print("----")
    print(result[0][0])
    print(result[0][1])

    for j in range(0, 917):
        for k in range(0, 6):
            cnt = int(result[j][k])
            myarray[cnt] += 1
            #print(myarray[1:45])

    print(myarray[1:46])

    x = []
    for n in range(1, 46):
        x.append(n)

    print(x)

    plt.xlabel('number')
    plt.ylabel('Number of Times')
    plt.xlim(0, 45)
    plt.ylim(0, 150)
    plt.plot(x, myarray[1:46], 'r')
    plt.show()


def nums():
    for i in (1, 46):
        result = analysis().myarray[i]





def main():
    #crawler()
    #insert()
    analysis()



if __name__ == "__main__":
    main()