CREATE DATABASE trash;

CREATE USER 'trash'@'%' IDENTIFIED BY 'trash';

GRANT ALL PRIVILEGES ON trash.* TO 'trash'@'%';

FLUSH PRIVILEGES;

DROP TABLE user;

CREATE TABLE user
(
    user_id   INT          NOT NULL AUTO_INCREMENT PRIMARY KEY,
    user_name VARCHAR(255) NOT NULL,
    account   VARCHAR(255) NOT NULL,
    password  VARCHAR(255) NOT NULL
);

DROP TABLE cluster;

CREATE TABLE `cluster`
(
    `cluster_id`   INT          NOT NULL AUTO_INCREMENT PRIMARY KEY,
    `cluster_name` VARCHAR(255) NOT NULL
);

DROP TABLE bin;

CREATE TABLE `bin`
(
    `id`                    INT          NOT NULL AUTO_INCREMENT PRIMARY KEY,
    `bin_id`                INT          NOT NULL,
    `cluster_id`            INT          NOT NULL,
    `bin_name`              VARCHAR(255) NOT NULL,
    `lid_count`             INT          NOT NULL,
    `residual_waste_count`  INT          NOT NULL,
    `recyclable_count`      INT          NOT NULL,
    `food_waste_count`      INT          NOT NULL,
    `hazardous_waste_count` INT          NOT NULL,
    `board_id`              VARCHAR(255) NOT NULL,
    `methane_value`         INT          NOT NULL,
    `smog_value`            INT          NOT NULL,
    `pos_x`                 DECIMAL(9, 6),
    `pos_y`                 DECIMAL(9, 6),
    `date`                  DATETIME     NOT NULL DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (`cluster_id`) REFERENCES `cluster` (`cluster_id`)
);

DROP TABLE event;

CREATE TABLE `event`
(
    `event_id`   INT          NOT NULL AUTO_INCREMENT PRIMARY KEY,
    `bin_id`     INT          NOT NULL,
    `event_name` VARCHAR(255) NOT NULL,
    `status`     VARCHAR(10)  NOT NULL,
    `trigger`    VARCHAR(10)  NOT NULL,
    `event_time` DATETIME     NOT NULL
);