import requests
import pandas as pd
apikey =  '5QV0KHMPIB0FN6Y38GVAVWYASDNROFGZ'

#Copy pasted from the api page under Resource URL
endpoint = "https://api.tdameritrade.com/v1/marketdata/chains"

def mainloop(df, stockname):
    # create a dict of all calls on an exp date by using 1st param of date and second param 'callExpDateMap'
    callslist = df.index

    def finddate(daysToExpiry):
        for i in range(len(callslist)):
            datestring = callslist[i]
            dateslist = datestring.split(':')
            # print(dateslist[1])
            if int(dateslist[1]) >= daysToExpiry:
                # print(dateslist[1])
                return callslist[i]
                break;

    shortcallData = (df.loc[finddate(40), 'callExpDateMap'])
    longcallData = (df.loc[finddate(180), 'callExpDateMap'])

    def callDataframe(callData, deltalow, deltahigh):
        keylist = []
        for key in callData:
            keylist.append(key)

        keys = ['description', 'strikePrice', 'mark', 'theta', 'daysToExpiration']
        df = pd.DataFrame()
        for i in keylist:
            tempstrikeCallData = callData[str(i)]
            strikeCallData = tempstrikeCallData[0]
            if ((float(strikeCallData['delta']) > deltalow) & (float(strikeCallData['delta']) < deltahigh)):
                wanted_keys = ['delta', 'mark', 'strikePrice', 'daysToExpiration']  # The keys you want
                datasubset = dict((k, strikeCallData[k]) for k in wanted_keys if
                                  k in strikeCallData)  # creates a subset dictionary with values of the keys provided
                df = df.append(datasubset, ignore_index=True)  # appends to pandas DataFrame
        return df

    shortdf = pd.DataFrame(callDataframe(shortcallData, .2, .4))
    longdf = pd.DataFrame(callDataframe(longcallData, .7, .9))
    expirationdates = str(shortdf.iloc[0, 0]) + ", " + str(longdf.iloc[0, 0])
    ######

    percentperday = []
    optionsdetails = []
    x = 1
    for i in range(len(shortdf)):
        shortmark = shortdf.iloc[i, 2]
        shortstrike = shortdf.iloc[i, 3]
        for e in range(len(longdf)):
            longmark = longdf.iloc[e, 2]
            longstrike = longdf.iloc[e, 3]

            if ((longmark + longstrike) <= shortstrike):
                percentperday.append(shortmark / longmark / shortdf.iloc[0, 0])
                optionsdetails.append(stockname + ":" + "Short strike: " + str(shortstrike) + ", Long strike: " + str(
                    longstrike) + ", Days to Expiry: " + expirationdates)



    selectedindex = percentperday.index(max(percentperday))
    stockspecificpercent = max(percentperday)
    stockspecificdetails = optionsdetails[selectedindex]

    totalpercent.append(stockspecificpercent)
    totaldetails.append(stockspecificdetails)

stocks = []
etfs = []
filePath = r"C:\Users\murar\PycharmProjects\Finance\Stock-ETFList.xlsx"

stocklist = pd.read_excel(filePath)

for i in range(len(stocklist.iloc[:,0])):
    if stocklist.iloc[i,0] != None:
        stocks.append(stocklist.iloc[i,0])

for i in range(len(stocklist.iloc[:,2])):
    if (stocklist.iloc[i,2] != None):
        etfs.append(stocklist.iloc[i,2])

totalpercent = []
totaldetails = []
for i in stocks:  #CHANGE TO etfs OR stocks BASED ON NEED
    # define params in a payload dictionary
    payload = {'apikey': '5QV0KHMPIB0FN6Y38GVAVWYASDNROFGZ',
               'symbol': i,
               'contractType': 'CALL',
               'includeQuotes': 'False',
               'toDate': '2024-10-30',
               'optionType': 'ALL',
               'range': 'ALL'}

    # make a request from the API
    content = requests.get(url=endpoint, params=payload)

    # convert data to dictionary
    data = content.json()

    # create a pandas dataframe with data
    df = pd.DataFrame(data)

    mainloop(df, i)


for i in range(len(totalpercent)):  #len(totalpercent)
    finalindex = totalpercent.index(max(totalpercent))
    print(str(i+1) + ": " + str(totalpercent[finalindex]))
    print("   " + str(totaldetails[finalindex]))
    totalpercent.pop(finalindex)
    totaldetails.pop(finalindex)