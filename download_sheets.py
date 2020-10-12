#!/usr/bin/python3
from bs4 import BeautifulSoup as Soup
from requests import get as GET
from os import mkdir
from os.path import exists
import re

def download_sheet(url):
    *_, fname = url.split('?')[0].split('/')
    if not exists('Sheets'): mkdir('Sheets')
    img_bytes = GET(url).content
    with open(f'Sheets/{fname}', 'wb') as f: f.write(img_bytes)

def get_sheets_url(proto, host, url):
    soup = Soup(GET(url).text, 'html.parser')
    imgs = soup.find('div', {'id': 'sheet-container'}).find_all('img')
    for img in imgs:
        if not 'src' in img.attrs: continue
        yield f'{proto}://{host}{img["src"]}'

def get_sprites(platform, game):
    proto, host = 'https', 'www.spriters-resource.com'
    abs_url = f'{proto}://{host}'
    url = f'{abs_url}/{platform}/{game}'
    pattern = f'{url}/sheet/'
    urls = Soup(GET(url).text, 'html.parser').find_all('a')
    for a in urls:
        if 'href' not in a.attrs: continue
        url = f'{abs_url}{a["href"]}' if a['href'][:1] == '/' else a['href']
        url = url if url[:4] == 'http' else f'{abs_url}/{a["href"]}'
        if not pattern in url: continue
        yield from get_sheets_url(proto, host, url)

if __name__ == '__main__':
    for sheet in get_sprites('snes', 'harvestmoon'):
        download_sheet(sheet)
