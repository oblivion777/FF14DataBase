CREATE TABLE `mods_test` (
  `id` int unsigned NOT NULL AUTO_INCREMENT,
  `filename` varchar(128) DEFAULT NULL,
  `type` enum('gear','hair','face','body','animation','other') DEFAULT NULL,  
  `path` varchar(256) DEFAULT NULL,
  `md5` char(37) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci



CREATE TABLE `mods` (
  `id` int unsigned NOT NULL AUTO_INCREMENT,
  `filename` varchar(128) DEFAULT NULL,
  `type` char(16) DEFAULT NULL,  
  `tag` varchar(128) DEFAULT NULL,  
  `path` varchar(256) DEFAULT NULL,
  `md5` char(37) DEFAULT NULL,
  `preview_pic_md5` varchar(140) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci