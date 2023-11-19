import datetime
import os
import webbrowser
import argparse
import urllib.request
import shutil

from urllib.error import HTTPError

YEAR = 2023
URL = "https://adventofcode.com/%d/day/%d"


def get_day():
    return datetime.datetime.today().day

def get_session():
    session = ""
    with open('session', 'r') as f:
        session = f.read()
    return session


def main(year = None, day = None):

    if day == None:
        day = get_day()

    if year == None:
        year = YEAR
    
    ### init workspace ###
    workspace_path = os.path.join(str(year), str(day))

    if not os.path.exists(workspace_path):
        os.makedirs(workspace_path, exist_ok=True)

    ### import basic project file in workspace
    try:
        shutil.copy2('basic.cpp', os.path.join(workspace_path, f'day{day}.cpp'))
    except Exception as e:
        print(e.__repr__())
        
    ### fetch input ###
    req = urllib.request.Request((URL+'/input') % (year, day), headers={'User-Agent': 'Mozilla/5.0', 'Cookie':f'session={get_session()}'})
    try:
        with urllib.request.urlopen(req) as r:
            with open( os.path.join(workspace_path, 'input') , 'wb') as f:
                f.write(r.read())
    except HTTPError as e:
        print(e.__repr__())
        print((URL+'/input') % (year, day))
    
    ### open browser ###
    try:
        webbrowser.open_new(URL % (year, day))
    except HTTPError as e:
        print(e.__repr__())
        print(URL) % (year, day)



if __name__ == '__main__':
    parser = argparse.ArgumentParser('init_day')
    parser.add_argument('-y', '--year', type = int, help = 'year of the challenge')
    parser.add_argument('-d', '--day', type = int, help = 'day of the challenge')

    args, unknown = parser.parse_known_args()
    main(args.year, args.day)