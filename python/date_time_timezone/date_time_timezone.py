from datetime import datetime
from zoneinfo import ZoneInfo


def main():
    system_current_datetime = datetime.now().astimezone()
    datetime_shanghai = system_current_datetime.astimezone(ZoneInfo("Asia/Shanghai"))
    datetime_newyork = system_current_datetime.astimezone(ZoneInfo("America/New_York"))
    datetime_london = system_current_datetime.astimezone(ZoneInfo("Europe/London"))
    print(f"ShangHai: {datetime_shanghai}")
    print(f"New York: {datetime_newyork}")
    print(f"London: {datetime_london}")


if __name__ == "__main__":
    main()

