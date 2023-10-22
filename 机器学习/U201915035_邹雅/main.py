import hashlib
import random
import csv
import json
from json import JSONDecodeError

import numpy as np
import pandas as pd
import time
from hashlib import md5
import traceback
import requests
import re

from sklearn.naive_bayes import MultinomialNB
from sklearn.linear_model import LogisticRegression
from sklearn.feature_extraction.text import CountVectorizer, TfidfVectorizer, TfidfTransformer
from sklearn import svm


def from_json_to_csv(json_path,csv_path):
    json_file = open(json_path,'r',encoding='utf-8')
    csv_file = open(csv_path,'w',newline='',encoding='utf-8')
    writer = csv.writer(csv_file)
    json_data = json.load(json_file)
    keys = json_data[0].keys()
    writer.writerow(keys)
    for data in json_data:
        writer.writerow(data.values())
    json_file.close()
    csv_file.close()

def get_label_array(json_path):
    json_file = open(json_path, 'r', encoding='utf-8')
    csv_file = open(r'./dataset/label.csv', 'w', newline='', encoding='utf-8')
    writer = csv.writer(csv_file)
    json_data = json.load(json_file)
    label_array = []
    for data in json_data:
        label_array.append(list(data.values())[1])
    writer.writerow(label_array)
    json_file.close()
    csv_file.close()

def stopword():
    """
    返回停用词词表
    :return:
    """
    stopword = []
    with open('./stopword/stopwords.txt', "r") as f:
        lines = (f.readlines())
        for item in lines:
            stopword.append(item.strip())
    return stopword

def splitToWords(texts):
    wordlists = []
    for text in texts:
        array = re.split('[ ,.!?]',text.strip())
        wordlists.append(array)
    return wordlists

def deleteDigitAndSpace(array):
    new_array = []
    for data_array in array:
        new_new_array = []
        for data in data_array:
            if not data.isdigit():
                if data != '':
                    new_new_array.append(data)
        new_array.append(new_new_array)
    return new_array

def deleteStopWords(array):
    print("### cleanup_stopword ###")
    stopword_set = set()
    with open("./stopword/stopwords.txt", "r", encoding="utf-8") as fr:
        words = fr.readline()
        while words:
            stopword_set.add(words.replace("\n", ""))
            words = fr.readline()
    return [[w for w in data if w not in stopword_set] for data in array], stopword_set

def translate(text):
    #http://api.fanyi.baidu.com/api/ 在这个网站申请APP id和对应密钥
    appId = '20211127001011400'
    secretKey = 'RZGgjWyK5jRij823VDCH'
    fromLang = 'auto'  # 自动选取语言，多语言无法规定
    language = 'en' #将所有语言翻译成英文
    #爬取数据的url
    url = 'http://api.fanyi.baidu.com/api/trans/vip/translate'
    #产生一个随机数
    salt = str(random.randint(31256, 66253))
    #生成md5
    sign = appId + text + salt + secretKey
    m1 = hashlib.md5()
    m1.update(sign.encode('utf-8'))
    sign = m1.hexdigest()

    headers = {'Content-Type': 'application/x-www-form-urlencoded'}
    params = {'appid': appId, 'q': text, 'from': fromLang, 'to': language, 'salt': salt, 'sign': sign}
    #sleep to avoid request too frequently
    time.sleep(1)
    #生成json文件
    tar = requests.post(url, params=params, headers=headers).json()
    res = tar['trans_result'][0]['dst']
    lens = len(tar['trans_result'])
    if lens > 1:
        for i in range(lens - 1):
            res = res + tar['trans_result'][i+1]['dst'] + '\n'
    return res

def translate_main():
    # 读文件
    translate_path = r'./dataset/train.csv'
    translate_file = pd.read_csv(translate_path, header=None, encoding='UTF-8')[0].values.tolist()

    translated_data = []
    notvalid_lists = []

    for index, translate_text in enumerate(translate_file):
        step = 13500
        point = 13500
        start = 0
        node_translate = ''
        while True:
            try:
                if len(translate_text) > point:
                    for i, element in enumerate(translate_text):
                        if element == '\n' and i > point:
                            point = point + step  # 切割点后移
                            original_text = translate_text[start:i + 1]  # 原文切割
                            node_translate += translate(original_text)
                            start = i + 1
                else:
                    node_translate = translate(translate_text)
                translated_data.append([node_translate])
                break
            except JSONDecodeError:
                notvalid_lists.append(index)
                break
            except BaseException:
                traceback.print_exc()
    print(notvalid_lists)
    #写入翻译的csv文件
    with open(r'./dataset/mytranslate_train.csv', 'w', encoding='UTF-8', newline='') as csv_write:
        for translated in translated_data:
            csv.writer(csv_write).writerow(translated)

def test_bayes():
    path = r'./dataset/train_translated.csv'
    file = pd.read_csv(path, header=None, encoding='UTF-8')[0].values.tolist()
    train_sample = np.array(file)

    path2 = r'./dataset/test_translated.csv'
    file2 = pd.read_csv(path2, header=None, encoding='UTF-8')[0].values.tolist()
    test_sample = np.array(file2)

    #去除第一行，本不属于数据集的一部分
    train_sample = train_sample[1:]
    test_sample = test_sample[1:]
    #文本向量化
    vec = CountVectorizer()
    X_train_count_vectorizer = vec.fit_transform(train_sample)
    X_test_count_vectorizer = vec.transform(test_sample)

    tfidf = TfidfTransformer()
    X_train = tfidf.fit_transform(X_train_count_vectorizer)
    X_test = tfidf.transform(X_test_count_vectorizer)

    get_label_array(r'./dataset/train.json')
    label_file = pd.read_csv(r'./dataset/label.csv', header=None, encoding='UTF-8').values.tolist()
    train_label_array = list(map(int,label_file[0]))
    del train_label_array[683]
    del train_label_array[1208]
    train_label = np.array(train_label_array)

    clf = MultinomialNB(alpha=0.01,fit_prior=False,class_prior=[0.51,0.58])

    clf.fit(X_train, train_label)

    result = clf.predict(X_test)
    result = np.insert(result,83,0)
    file_handle = open('./dataset/result.txt', mode='w')
    for i in result:
        print(i)
        file_handle.write(str(i)+'\n')
    file_handle.close()

def logistic():
    path = r'./dataset/train_translated.csv'
    file = pd.read_csv(path, header=None, encoding='UTF-8')[0].values.tolist()
    train_sample = np.array(file)

    path2 = r'./dataset/test_translated.csv'
    file2 = pd.read_csv(path2, header=None, encoding='UTF-8')[0].values.tolist()
    test_sample = np.array(file2)

    # 去除第一行，本不属于数据集的一部分
    train_sample = train_sample[1:]
    test_sample = test_sample[1:]

    get_label_array(r'./dataset/train.json')
    label_file = pd.read_csv(r'./dataset/label.csv', header=None, encoding='UTF-8').values.tolist()
    train_label_array = list(map(int, label_file[0]))
    del train_label_array[683]
    del train_label_array[1208]
    train_label = np.array(train_label_array)

    stop_list = stopword()
    vec = TfidfVectorizer(stop_words=stop_list)
    xTrain_tfidf = vec.fit_transform(train_sample)
    xTest_tfidf = vec.transform(test_sample)
    clf = LogisticRegression(multi_class = 'multinomial', solver='lbfgs')
    clf.fit(xTrain_tfidf, train_label)
    preds = clf.predict_proba(xTest_tfidf)
    preds = np.argmax(preds, axis=1)
    preds = np.insert(preds, 83, 0)
    file_handle = open('./dataset/logistic_result.txt', mode='w')
    for i in preds:
        print(i)
        file_handle.write(str(i) + '\n')
    file_handle.close()

def svm_main():
    path = r'./dataset/train_translated.csv'
    file = pd.read_csv(path, header=None, encoding='UTF-8')[0].values.tolist()
    train_sample = np.array(file)

    path2 = r'./dataset/test_translated.csv'
    file2 = pd.read_csv(path2, header=None, encoding='UTF-8')[0].values.tolist()
    test_sample = np.array(file2)

    # 去除第一行，本不属于数据集的一部分
    train_sample = train_sample[1:]
    test_sample = test_sample[1:]

    get_label_array(r'./dataset/train.json')
    label_file = pd.read_csv(r'./dataset/label.csv', header=None, encoding='UTF-8').values.tolist()
    train_label_array = list(map(int, label_file[0]))
    del train_label_array[683]
    del train_label_array[1208]
    train_label = np.array(train_label_array)

    stop_list = stopword()
    vec = TfidfVectorizer(stop_words=stop_list)
    xTrain_tfidf = vec.fit_transform(train_sample)
    xTest_tfidf = vec.transform(test_sample)

    lin_clf = svm.LinearSVC()
    lin_clf.fit(xTrain_tfidf, train_label)
    # 预测测试集，并生成结果提交
    preds = lin_clf.predict(xTest_tfidf)
    preds = np.insert(preds, 83, 0)
    file_handle = open('./dataset/svm_result.txt', mode='w')
    for i in preds:
        print(i)
        file_handle.write(str(i) + '\n')
    file_handle.close()

if __name__ == '__main__':
    svm_main()




