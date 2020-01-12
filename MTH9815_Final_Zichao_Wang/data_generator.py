# data_generator.py
# Created by Zichao Wang
# Date: Dec 8, 2018

# generate prices.txt, trades.txt, market_data.txt of given size.


import numpy as np
import csv


# prices.txt
# n is data size.
def price_generator(n):
    with open('C:\\Users\\Zichao Wang\\Desktop\\Baruch\\Fall Semester\\Software Engineering\\MTH9815_Final_Zichao_Wang\\prices.txt', 'w', newline = '') as f:
        writer = csv.writer(f, delimiter = ',')
        
        # generate n pieces of data.
        for i in range(n):
            # CUSIP data fetched from 'https://www.treasurydirect.gov/instit/instit.htm' on Dec 8, 2018.
            cusip_dic = {1 : '9128285Q9', 2 : '9128285L0', 3 : '9128285P1', 4 : '9128285N6', 5 : '9128285M8', 6 : '912810SE9'}
            data_cusip = [cusip_dic[np.random.randint(1, 7)]]
            data_prefix = str(np.random.randint(99, 101))
            data_mid = str(np.random.randint(0, 32)).zfill(2)
            data_suffix = str(np.random.randint(0, 8))
            data = data_prefix + '-' + data_mid + data_suffix
            data = [data]
            
            # spread = (1/128) * spread
            spread = [str(np.random.randint(1, 3))]
            writer.writerow(data_cusip + data + spread)
    
    f.close()
            

price_generator(10)



# trades.txt
# n is data size.
def trade_generator(n):
    with open('C:\\Users\\Zichao Wang\\Desktop\\Baruch\\Fall Semester\\Software Engineering\\MTH9815_Final_Zichao_Wang\\trades.txt', 'w', newline = '') as f:
        writer = csv.writer(f, delimiter = ',')
        
        # generate n pieces of data.
        for i in range(n):
            # CUSIP data fetched from 'https://www.treasurydirect.gov/instit/instit.htm' on Dec 8, 2018.
            cusip_dic = {1 : '9128285Q9', 2 : '9128285L0', 3 : '9128285P1', 4 : '9128285N6', 5 : '9128285M8', 6 : '912810SE9'}
            data_cusip = [cusip_dic[np.random.randint(1, 7)]]
            trade = ['Trade' + str(np.random.randint(1, 3))]
            book = ['TRSY' + str(np.random.randint(1, 4))]
            
            data_prefix = str(np.random.randint(99, 101))
            data_mid = str(np.random.randint(0, 32)).zfill(2)
            data_suffix = str(np.random.randint(0, 8))
            data = data_prefix + '-' + data_mid + data_suffix
            data = [data]
            
            quantity = [str(np.random.randint(1, 6) * 1000000)]
            pos_dic = {1 : 'BUY', 2 : 'SELL'}
            pos = [pos_dic[np.random.randint(1, 3)]]
            
            writer.writerow(data_cusip + trade + book + data + quantity + pos)
    
    f.close()
    
trade_generator(10)


# marketdata.txt
# n is data size.
def market_data_generator(n):
    with open('C:\\Users\\Zichao Wang\\Desktop\\Baruch\\Fall Semester\\Software Engineering\\MTH9815_Final_Zichao_Wang\\marketdata.txt', 'w', newline = '') as f:
        writer = csv.writer(f, delimiter = ',')
        
        for _ in range(n):
            # generate CUSIP
            cusip_dic = {1 : '9128285Q9', 2 : '9128285L0', 3 : '9128285P1', 4 : '9128285N6', 5 : '9128285M8', 6 : '912810SE9'}
            data_cusip = [cusip_dic[np.random.randint(1, 7)]]
            
            # generate 10 orders for each selected bond.
            # we represent this by just generating mid price and spread,
            # assuming all adjacent order on both side have difference 1/128 usd in price.
            
            # first generate mid price.
            data_prefix = str(np.random.randint(99, 101))
            data_mid = str(np.random.randint(0, 32)).zfill(2)
            data_sufix = str(np.random.randint(0, 8))
            data = [data_prefix + '-' + data_mid + data_sufix]
            
            # then generate spread value = spread * 1/128 usd.
            spread = [np.random.randint(1, 5)]
                
            writer.writerow(data_cusip + data + spread)
            
    f.close()
    
market_data_generator(10)


# inquiries.txt
# n is data size
def inquiry_generator(n):
    with open('C:\\Users\\Zichao Wang\\Desktop\\Baruch\\Fall Semester\\Software Engineering\\MTH9815_Final_Zichao_Wang\\inquiries.txt', 'w', newline = '') as f:
        writer = csv.writer(f, delimiter = ',')
        for i in range(n):
            cusip_dic = {1 : '9128285Q9', 2 : '9128285L0', 3 : '9128285P1', 4 : '9128285N6', 5 : '9128285M8', 6 : '912810SE9'}
            data_id = [cusip_dic[np.random.randint(1, 7)]]
            
            inquiry_id = ['I' + str(i)]
            
            data_prefix = str(np.random.randint(99, 101))
            data_mid = str(np.random.randint(0, 32)).zfill(2)
            data_sufix = str(np.random.randint(0, 8))
            data = [data_prefix + '-' + data_mid + data_sufix]
            
            quantity = [str(np.random.randint(1, 10) * 1000000)]
            
            pos_dic = {1: 'BUY', 2: 'SELL'}
            pos = [pos_dic[np.random.randint(1, 3)]]
            
            #state_dic = {1: 'RECEIVED', 2: 'QUOTED', 3: 'DONE', 4: 'REJECTED', 5: 'CUSTOMER_REJECTED'}
            #state = [state_dic[np.random.randint(1, 6)]]
            
            writer.writerow(data_id + inquiry_id + data + quantity + pos)
    f.close()
    
inquiry_generator(10)