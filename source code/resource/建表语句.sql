| mods  | CREATE TABLE `mods` (
  `id` int unsigned NOT NULL AUTO_INCREMENT,
  `filename` varchar(128) DEFAULT NULL,
  `type` enum('gear','hair','face','body','animation','other','unclassify') CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT 'unclassify',
  `path` varchar(256) DEFAULT NULL,
  `md5` char(37) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci |





insert into mods_test(filename,md5) value('asd','dddf')
where not exists(select filename,md5 from mods_test where filename='asd' and md5='dddf52');