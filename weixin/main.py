#!/usr/bin/python3

import random
import sxtwl
from time import time, localtime
import cityinfo
from requests import get, post
from datetime import datetime, date
import sys


def get_color():
    # 获取随机颜色
    get_colors = lambda n: list(map(lambda i: "#" + "%06x" % random.randint(0, 0xFFFFFF), range(n)))
    color_list = get_colors(100)
    return random.choice(color_list)


def get_access_token():
    # appId
    app_id = "wxe0f9c8825b0df173"
    # appSecret
    app_secret = "ff9b92abf43d78d222281b9b4839d221"
    post_url = ("https://api.weixin.qq.com/cgi-bin/token?grant_type=client_credential&appid={}&secret={}"
                .format(app_id, app_secret))
    try:
        access_token = get(post_url).json()['access_token']
    except KeyError:
        print("获取access_token失败，请检查app_id和app_secret是否正确")
        sys.exit(1)
    # print(access_token)
    return access_token


def get_weather(province, city):
    # 城市id
    try:
        city_id = cityinfo.cityInfo[province][city]["AREAID"]
    except KeyError:
        print("推送消息失败，请检查省份或城市是否正确")
        sys.exit(1)
    # city_id = 101280101
    # 毫秒级时间戳
    t = (int(round(time() * 1000)))
    headers = {
        "Referer": "http://www.weather.com.cn/weather1d/{}.shtml".format(city_id),
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) '
                      'AppleWebKit/537.36 (KHTML, like Gecko) Chrome/103.0.0.0 Safari/537.36'
    }
    url = "http://d1.weather.com.cn/dingzhi/{}.html?_={}".format(city_id, t)
    response = get(url, headers=headers)
    response.encoding = "utf-8"
    response_data = response.text.split(";")[0].split("=")[-1]
    response_json = eval(response_data)
    # print(response_json)
    weatherinfo = response_json["weatherinfo"]
    # 天气
    weather = weatherinfo["weather"]
    # 最高气温
    temp = weatherinfo["temp"]
    # 最低气温
    tempn = weatherinfo["tempn"]
    return weather, temp, tempn


def get_birthday(birthday):
    birthday = "2002-07-19"
    today_year = localtime().tm_year
    today_month = localtime().tm_mon
    today_day = localtime().tm_mday
    birthYear = today_year
    solarBirthDay = sxtwl.fromLunar(birthYear, int(birthday.split("-")[1]), int(birthday.split("-")[2]))
    solar_mongth = solarBirthDay.getSolarMonth()
    solar_day = solarBirthDay.getSolarDay()

    if solar_mongth <= today_month and solar_day < today_day:
        birthYear +=1
        solarBirthDay = sxtwl.fromLunar(birthYear, int(birthday.split("-")[1]), int(birthday.split("-")[2]))
        solar_mongth = solarBirthDay.getSolarMonth()
        solar_day = solarBirthDay.getSolarDay()

    today = datetime.date(datetime(year=today_year, month=today_month, day=today_day))
    year_date = date(birthYear, solar_mongth, solar_day)
    if today > year_date:
        birth_date = date((today_year + 1), solar_mongth, solar_day)
        birth_day = str(birth_date.__sub__(today)).split(" ")[0]
    elif today == year_date:
        birth_day = 0
    else:
        birth_date = year_date
        birth_day = str(birth_date.__sub__(today)).split(" ")[0]
    return birth_day


def get_ciba():
    url = "http://open.iciba.com/dsapi/"
    headers = {
        'Content-Type': 'application/json',
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) '
                      'AppleWebKit/537.36 (KHTML, like Gecko) Chrome/103.0.0.0 Safari/537.36'
    }
    r = get(url, headers=headers)
    note_en = r.json()["content"]
    note_ch = r.json()["note"]
    return note_ch, note_en


def send_message(to_user, access_token, city_name, weather, max_temperature, min_temperature, note_ch, note_en):
    url = "https://api.weixin.qq.com/cgi-bin/message/template/send?access_token={}".format(access_token)
    week_list = ["星期日", "星期一", "星期二", "星期三", "星期四", "星期五", "星期六"]
    year = localtime().tm_year
    month = localtime().tm_mon
    day = localtime().tm_mday
    today = datetime.date(datetime(year=year, month=month, day=day))
    week = week_list[today.isoweekday() % 7]
    loveday_txt = "2022-05-03"
    love_year = int(loveday_txt.split("-")[0])
    love_month = int(loveday_txt.split("-")[1])
    love_day = int(loveday_txt.split("-")[2])
    love_date = date(love_year, love_month, love_day)
    love_days = str(today.__sub__(love_date)).split(" ")[0]

    birthTxt = "距离傻倩的生日还有"
    reminderBitDay =  get_birthday("2002-07-19")
    dayTxt = "天"
    if reminderBitDay == 0:
        birthTxt =  "今天傻倩生日了"
        reminderBitDay = ""
        dayTxt = ""
    data = {
        "touser": to_user,
        "template_id": "jzzx9Ucy-hNNhslp8AdFRrSgXu_SIP4-8itoLLxRw2I",
        "url": "http://weixin.qq.com/download",
        "topcolor": "#FF0000",
        "data": {
            "date": {
                "value": "{} {}".format(today, week),
                "color": get_color()
            },
            "city": {
                "value": city_name,
                "color": get_color()
            },
            "weather": {
                "value": weather,
                "color": get_color()
            },
            "min_temperature": {
                "value": min_temperature,
                "color": get_color()
            },
            "max_temperature": {
                "value": max_temperature,
                "color": get_color()
            },
            "love_day": {
                "value": love_days,
                "color": get_color()
            },
            "note_en": {
                "value": note_en,
                "color": get_color()
            },
            "note_ch": {
                "value": note_ch,
                "color": get_color()
            },
            "birth_txt" : {
                "value": birthTxt
            },
            "birthday": {
                "value": reminderBitDay,
                "color": get_color()
            },
            "day_txt": {
                "value": dayTxt,
            }
        }
    }
    headers = {
        'Content-Type': 'application/json',
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) '
                      'AppleWebKit/537.36 (KHTML, like Gecko) Chrome/103.0.0.0 Safari/537.36'
    }
    response = post(url, headers=headers, json=data).json()
    if response["errcode"] == 40037:
        print("推送消息失败，请检查模板id是否正确")
    elif response["errcode"] == 40036:
        print("推送消息失败，请检查模板id是否为空")
    elif response["errcode"] == 40003:
        print("推送消息失败，请检查微信号是否正确")
    elif response["errcode"] == 0:
        print("推送消息成功", datetime.today())
    else:
        print(response)


if __name__ == "__main__":
    # 获取accessToken
    accessToken = get_access_token()
    # 接收的用户
    users = ["opJ1j6AOjmbw92k4kKoklCU__JOE", "opJ1j6CRc2_4Gyi5UV7XiEDsv78M"]
    # 传入省份和市获取天气信息
    province, city = "贵州", "贵阳"
    weather, max_temperature, min_temperature = get_weather(province, city)
    # 获取词霸每日金句
    note_ch, note_en = get_ciba()
    # 公众号推送消息
    for user in users:
        send_message(user, accessToken, city, weather, max_temperature, min_temperature, note_ch, note_en)
