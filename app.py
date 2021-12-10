import json
import argparse
import logging
import spotipy
from spotipy.oauth2 import SpotifyOAuth


logger = logging.getLogger('examples.artist_recommendations')
logging.basicConfig(level='INFO')

sp = spotipy.Spotify(auth_manager=SpotifyOAuth(client_id='a2c722f716964e1fb30c048b086cc58a',client_secret='dd03145fa9c14e33b2fc98915a4d6ba0',redirect_uri='http://localhost:8888/callback',scope="playlist-modify-public"))
user_id = sp.me()['id']

def get_args():
    parser = argparse.ArgumentParser(description='Recommendations for the '
                                     'given artist')
    parser.add_argument('-a', '--artist', required=True, help='Name of Artist')
    return parser.parse_args()


def get_track(name):
    results = sp.search(q='track:' + name, type='track')
    items = results['tracks']['items']
    if len(items) > 0:
        return items[0]
    else:
        return None


def show_recommendations_for_track(track):
    results = sp.recommendations(seed_tracks=[track['id']],limit=50)
    sp.playlist_replace_items("7lDLwz4UXBQXkrtJjf6ibV", [track['id']])
    for track in results['tracks']:
        logger.info('Recommendation: %s - %s', track['name'],
                    track['artists'][0]['name'])
        sp.playlist_add_items("7lDLwz4UXBQXkrtJjf6ibV", [track['uri']])

        
def main():
    args = get_args()
    track = get_track(args.artist)
    if track:
        show_recommendations_for_track(track)
    else:
        logger.error("Can't find that artist", args.artist)


if __name__ == '__main__':
    main()