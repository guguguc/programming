headers = {
    "user-agent":
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36"
}
cookies = {
    "T_WM": "48006617374",
    "SCF":
        "Apy097ZCCps4raq8Vak6EclcDTnVbRHotrL1kjvg0HhijCiQ5tx1fjNRHoOOepPEF-LGgptwgd60d949_PPNL50.",
    "SUB":
        "_2A25N_5P1DeRhGeBP6VQS8C3JyD-IHXVvAz29rDV6PUJbkdAKLU_ikW1NRWejPY-DN--BzH5MBviwbw_E66Bu54SF",
    "SUBP":
        "0033WrSXqPxfM725Ws9jqgMF55529P9D9W5v1ED0B0LiqpSlMv3MxhXd5JpX5KMhUgL.Foqpeoq0ehefe0e2dJLoI7UrUgUf9NHo",
    "MLOGIN": "1",
    "M_WEIBOCN_PARAMS":
        "oid%3D4662543623130610%26luicode%3D10000011%26lfid%3D231093_-_selffollowed%26fid%3D231093_-_selffollowed%26uicode%3D10000011",
    "XSRF-TOKEN": "410d4e",
    "WEIBOCN_FROM": "1110006030"
}
proxies = {
    'http': 'http://127.0.0.1:10809',
    'https': 'http://127.0.0.1:10809'
}

"""followers api返回json
{
    ‘ok': 1,
    'data': {
        'cardlistInfo'：{
        }
    }，
    ’cards': [
    {}
    {'card_type':xx,
     'item_id':xx,
     'card_group':[{follower1}, {follower2}, {follower3}]}
    ]
}
"""

info_url = "https://m.weibo.cn/profile/info?uid={id}"
follower_url = "https://m.weibo.cn/api/container/getIndex?containerid=231051_-_followers_-_{id}"
fans_url = "https://m.weibo.cn/api/container/getIndex?containerid=231051_-_fans_-_{id}"
