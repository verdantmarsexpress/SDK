import updater
import myriota_auth
from myriota_download import get_download_url, download_file


def download_system_image():
    token = myriota_auth.auth()["IdToken"]

    s3_url = get_download_url(token, "system_image_1_5_6.bin")

    download_file(s3_url, "system.img")

#    updater

    


if __name__ == "__main__":
    download_system_image()

