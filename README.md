# C4Win course - Multi Thread Assignment

- Đã cài đặt tất cả chức năng đã yêu cầu.
- Lập trình hướng đối tượng, thiết kế class diagram.
- Tận dụng code shapes, attributes đã code ở những tuần trước.
- Cho phép chỉnh số thùng, tốc độ di chuyển của mỗi thùng. (Menu Item Settings)
- Chỉnh tốc độ di chuyển trực tiếp, kéo thanh trượt xem kết quả liền.
- Dùng kĩ thuật MemDC & Bitblt để vẽ không bị lag giật.
- Có thể chỉnh sữa dễ dàng chiều rộng của ống (các line), chiều cao, rộng của thùng, khoảng cách các thùng, số thùng mặc định, tốc độ mặc định,.. trong file Config.cpp
const int Config::BUCKET_WIDTH = 100;
const int Config::BUCKET_HEIGHT = 100;
const int Config::PIPE_WIDTH = 120;
const int Config::DISTANCE_BETWEEN_ADJACENT_BUCKETS = 120;
const int Config::DEFAULT_NUMBER_OF_BUCKETS = 20;
const int Config::DEFAULT_MOVING_SPEEED = 5; //Slider chạy từ 1 đến 10

Video demo: https://youtu.be/x22_qbrlJdU

# Screenshot
![Screenshot](https://raw.githubusercontent.com/hiepxuan2008/C4Win_MultiThreadRobot/master/Screenshot.png)