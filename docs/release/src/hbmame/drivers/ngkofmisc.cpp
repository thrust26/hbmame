// license:BSD-3-Clause
// copyright-holders:Robbbert
// Miscellaneous King of Fighters games
// kog, cthd, kof2k4, kof10th etc
// Nudity warning in Kof Special Edition 2004, stage with boats in the background:
//              There's a nude woman at the right side.
//              Sometimes the 6 women in the centre can also be nude.



// This fixes the Cart Jumper in KOGD
static MACHINE_CONFIG_DERIVED_CLASS( hbmame_kog, neogeo_arcade, neogeo_hbmame )
	MCFG_CPU_MODIFY("maincpu")
	MCFG_CPU_PROGRAM_MAP(main_map_noslot)
	MCFG_KOG_PROT_ADD("kog_prot")
MACHINE_CONFIG_END

DRIVER_INIT_MEMBER( neogeo_hbmame, kogd )
{
	DRIVER_INIT_CALL(neogeo);
	m_kog_prot->kog_install_protection(m_maincpu);
}

DRIVER_INIT_MEMBER( neogeo_hbmame, kof10thu )
{
	UINT32 tsize = m_region_maincpu->bytes();
	UINT8 *rom = m_region_maincpu->base();
	UINT32 i, ofst;
	dynamic_buffer trom( tsize );
	memcpy( &trom[ 0 ], &rom[ 0 ], tsize );
	// We unscramble the lower 6 address lines of the program rom.
	for( i = 0; i < tsize / 2; i++ )
	{
		ofst = BITSWAP8( (i & 0x0000ff), 7, 6, 2, 3, 4, 5, 0, 1 ) | (i & 0xffff00);
		memcpy( &rom[ ofst * 2 ], &trom[ i * 2 ], 2 );
	}

	DRIVER_INIT_CALL(neogeo);
}



ROM_START( cthd2k3b ) /* Crouching Tiger Hidden Dragon 2003 - Hack by HunterX Hacker - (Can choose Zero and Igniz) */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "360b.p1", 0x000000, 0x100000, CRC(f403c9b3) SHA1(35D52B9388D4715BACBE958ACCD133C19E769E30) )
	ROM_LOAD16_WORD_SWAP( "5003-p2.bin", 0x100000, 0x400000, CRC(adc1c22b) SHA1(271e0629989257a0d21d280c05df53df259414b1) )

	NEO_SFIX_128K( "5003-s1.bin", CRC(5ba29aab) SHA1(e7ea67268a10243693bff722e6fd2276ca540acf) )

	NEO_BIOS_AUDIO_128K( "5003-m1.bin", CRC(1a8c274b) SHA1(5f6f9c533f4a296a18c741ce59a69cf6f5c836b9) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "262-v1-08-e0.v1", 0x000000, 0x400000, CRC(83d49ecf) SHA1(2f2c116e45397652e77fcf5d951fa5f71b639572) )
	ROM_LOAD( "262-v2-08-e0.v2", 0x400000, 0x400000, CRC(003f1843) SHA1(bdd58837ad542548bd4053c262f558af88e3b989) )
	ROM_LOAD( "262-v3-08-e0.v3", 0x800000, 0x400000, CRC(2ae38dbe) SHA1(4e82b7dd3b899d61907620517a5a27bdaba0725d) )
	ROM_LOAD( "262-v4-08-e0.v4", 0xc00000, 0x400000, CRC(26ec4dd9) SHA1(8bd68d95a2d913be41a51f51e48dbe3bff5924fb) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "5003-c1.bin", 0x0000000, 0x800000, CRC(68f54b67) SHA1(e2869709b11ea2846799fe431211c83e928e103e) )
	ROM_LOAD16_BYTE( "5003-c2.bin", 0x0000001, 0x800000, CRC(2f8849d5) SHA1(7ef74981aa056f5acab4ddabffd3e98b4cb970be) )
	ROM_LOAD16_BYTE( "5003-c3.bin", 0x1000000, 0x800000, CRC(ac4aff71) SHA1(c983f642e68deaa40fee3e208f2dd55f3bacbdc1) )
	ROM_LOAD16_BYTE( "5003-c4.bin", 0x1000001, 0x800000, CRC(afef5d66) SHA1(39fe785563fbea54bba88de60dcc62e2458bd74a) )
	ROM_LOAD16_BYTE( "5003-c5.bin", 0x2000000, 0x800000, CRC(c7c1ae50) SHA1(f54f5be7513a5ce2f01ab107a2b26f6a9ee1f2a9) )
	ROM_LOAD16_BYTE( "5003-c6.bin", 0x2000001, 0x800000, CRC(613197f9) SHA1(6d1fefa1be81b79e251e55a1352544c0298e4674) )
	ROM_LOAD16_BYTE( "5003-c7.bin", 0x3000000, 0x800000, CRC(64ddfe0f) SHA1(361f3f4618009bf6419961266eb9ab5002bef53c) )
	ROM_LOAD16_BYTE( "5003-c8.bin", 0x3000001, 0x800000, CRC(917a1439) SHA1(6f28d1d7c6edee1283f25e632c69204dbebe40af) )
ROM_END

ROM_START( ct2k3eh ) /* Crouching Tiger Hidden Dragon 2003 - Enhance by Fighters Kim and HunterX Hacker - (Can choose Zero and Igniz - power hack) */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "360eh.p1",    0x000000, 0x100000, CRC(eac4773b) SHA1(7E8AF18D5A18B3FE0B9130C66D8F4EF6297B8C7F) )
	ROM_LOAD16_WORD_SWAP( "5003-p2.bin", 0x100000, 0x400000, CRC(adc1c22b) SHA1(271e0629989257a0d21d280c05df53df259414b1) )

	NEO_SFIX_128K( "5003-s1.bin", CRC(5ba29aab) SHA1(e7ea67268a10243693bff722e6fd2276ca540acf) )

	NEO_BIOS_AUDIO_128K( "5003-m1.bin", CRC(1a8c274b) SHA1(5f6f9c533f4a296a18c741ce59a69cf6f5c836b9) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "262-v1-08-e0.v1", 0x000000, 0x400000, CRC(83d49ecf) SHA1(2f2c116e45397652e77fcf5d951fa5f71b639572) )
	ROM_LOAD( "262-v2-08-e0.v2", 0x400000, 0x400000, CRC(003f1843) SHA1(bdd58837ad542548bd4053c262f558af88e3b989) )
	ROM_LOAD( "262-v3-08-e0.v3", 0x800000, 0x400000, CRC(2ae38dbe) SHA1(4e82b7dd3b899d61907620517a5a27bdaba0725d) )
	ROM_LOAD( "262-v4-08-e0.v4", 0xc00000, 0x400000, CRC(26ec4dd9) SHA1(8bd68d95a2d913be41a51f51e48dbe3bff5924fb) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "5003-c1.bin", 0x0000000, 0x800000, CRC(68f54b67) SHA1(e2869709b11ea2846799fe431211c83e928e103e) )
	ROM_LOAD16_BYTE( "5003-c2.bin", 0x0000001, 0x800000, CRC(2f8849d5) SHA1(7ef74981aa056f5acab4ddabffd3e98b4cb970be) )
	ROM_LOAD16_BYTE( "5003-c3.bin", 0x1000000, 0x800000, CRC(ac4aff71) SHA1(c983f642e68deaa40fee3e208f2dd55f3bacbdc1) )
	ROM_LOAD16_BYTE( "5003-c4.bin", 0x1000001, 0x800000, CRC(afef5d66) SHA1(39fe785563fbea54bba88de60dcc62e2458bd74a) )
	ROM_LOAD16_BYTE( "5003-c5.bin", 0x2000000, 0x800000, CRC(c7c1ae50) SHA1(f54f5be7513a5ce2f01ab107a2b26f6a9ee1f2a9) )
	ROM_LOAD16_BYTE( "5003-c6.bin", 0x2000001, 0x800000, CRC(613197f9) SHA1(6d1fefa1be81b79e251e55a1352544c0298e4674) )
	ROM_LOAD16_BYTE( "5003-c7.bin", 0x3000000, 0x800000, CRC(64ddfe0f) SHA1(361f3f4618009bf6419961266eb9ab5002bef53c) )
	ROM_LOAD16_BYTE( "5003-c8.bin", 0x3000001, 0x800000, CRC(917a1439) SHA1(6f28d1d7c6edee1283f25e632c69204dbebe40af) )
ROM_END

ROM_START( ct2k3k3 ) /* Crouching Tiger Hidden Dragon 2003 - Remix by Jason/K3 - (Character move change - V1.2 20030823) */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "360k3.p1",    0x000000, 0x100000, CRC(f5f1cfb2) SHA1(F0E19AE063E771567B30B52710C143B5E72CBF5A) )
	ROM_LOAD16_WORD_SWAP( "5003-p2.bin", 0x100000, 0x400000, CRC(adc1c22b) SHA1(271e0629989257a0d21d280c05df53df259414b1) )

	NEO_SFIX_128K( "5003-s1.bin", CRC(5ba29aab) SHA1(e7ea67268a10243693bff722e6fd2276ca540acf) )

	NEO_BIOS_AUDIO_128K( "5003-m1.bin", CRC(1a8c274b) SHA1(5f6f9c533f4a296a18c741ce59a69cf6f5c836b9) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "262-v1-08-e0.v1", 0x000000, 0x400000, CRC(83d49ecf) SHA1(2f2c116e45397652e77fcf5d951fa5f71b639572) )
	ROM_LOAD( "262-v2-08-e0.v2", 0x400000, 0x400000, CRC(003f1843) SHA1(bdd58837ad542548bd4053c262f558af88e3b989) )
	ROM_LOAD( "262-v3-08-e0.v3", 0x800000, 0x400000, CRC(2ae38dbe) SHA1(4e82b7dd3b899d61907620517a5a27bdaba0725d) )
	ROM_LOAD( "262-v4-08-e0.v4", 0xc00000, 0x400000, CRC(26ec4dd9) SHA1(8bd68d95a2d913be41a51f51e48dbe3bff5924fb) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "5003-c1.bin", 0x0000000, 0x800000, CRC(68f54b67) SHA1(e2869709b11ea2846799fe431211c83e928e103e) )
	ROM_LOAD16_BYTE( "5003-c2.bin", 0x0000001, 0x800000, CRC(2f8849d5) SHA1(7ef74981aa056f5acab4ddabffd3e98b4cb970be) )
	ROM_LOAD16_BYTE( "5003-c3.bin", 0x1000000, 0x800000, CRC(ac4aff71) SHA1(c983f642e68deaa40fee3e208f2dd55f3bacbdc1) )
	ROM_LOAD16_BYTE( "5003-c4.bin", 0x1000001, 0x800000, CRC(afef5d66) SHA1(39fe785563fbea54bba88de60dcc62e2458bd74a) )
	ROM_LOAD16_BYTE( "5003-c5.bin", 0x2000000, 0x800000, CRC(c7c1ae50) SHA1(f54f5be7513a5ce2f01ab107a2b26f6a9ee1f2a9) )
	ROM_LOAD16_BYTE( "5003-c6.bin", 0x2000001, 0x800000, CRC(613197f9) SHA1(6d1fefa1be81b79e251e55a1352544c0298e4674) )
	ROM_LOAD16_BYTE( "5003-c7.bin", 0x3000000, 0x800000, CRC(64ddfe0f) SHA1(361f3f4618009bf6419961266eb9ab5002bef53c) )
	ROM_LOAD16_BYTE( "5003-c8.bin", 0x3000001, 0x800000, CRC(917a1439) SHA1(6f28d1d7c6edee1283f25e632c69204dbebe40af) )
ROM_END

ROM_START( ct2k3k3o ) /* [OLD] Crouching Tiger Hidden Dragon 2003 - Remix by Jason/K3 - (Character move change 20030818) */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "360k3o.p1",   0x000000, 0x100000, CRC(93b2cb2b) SHA1(dc6bacae8851ab74eaf45c4392fdab0d679a266f) )
	ROM_LOAD16_WORD_SWAP( "5003-p2.bin", 0x100000, 0x400000, CRC(adc1c22b) SHA1(271e0629989257a0d21d280c05df53df259414b1) )

	NEO_SFIX_128K( "5003-s1.bin", CRC(5ba29aab) SHA1(e7ea67268a10243693bff722e6fd2276ca540acf) )

	NEO_BIOS_AUDIO_128K( "5003-m1.bin", CRC(1a8c274b) SHA1(5f6f9c533f4a296a18c741ce59a69cf6f5c836b9) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "262-v1-08-e0.v1", 0x000000, 0x400000, CRC(83d49ecf) SHA1(2f2c116e45397652e77fcf5d951fa5f71b639572) )
	ROM_LOAD( "262-v2-08-e0.v2", 0x400000, 0x400000, CRC(003f1843) SHA1(bdd58837ad542548bd4053c262f558af88e3b989) )
	ROM_LOAD( "262-v3-08-e0.v3", 0x800000, 0x400000, CRC(2ae38dbe) SHA1(4e82b7dd3b899d61907620517a5a27bdaba0725d) )
	ROM_LOAD( "262-v4-08-e0.v4", 0xc00000, 0x400000, CRC(26ec4dd9) SHA1(8bd68d95a2d913be41a51f51e48dbe3bff5924fb) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "5003-c1.bin", 0x0000000, 0x800000, CRC(68f54b67) SHA1(e2869709b11ea2846799fe431211c83e928e103e) )
	ROM_LOAD16_BYTE( "5003-c2.bin", 0x0000001, 0x800000, CRC(2f8849d5) SHA1(7ef74981aa056f5acab4ddabffd3e98b4cb970be) )
	ROM_LOAD16_BYTE( "5003-c3.bin", 0x1000000, 0x800000, CRC(ac4aff71) SHA1(c983f642e68deaa40fee3e208f2dd55f3bacbdc1) )
	ROM_LOAD16_BYTE( "5003-c4.bin", 0x1000001, 0x800000, CRC(afef5d66) SHA1(39fe785563fbea54bba88de60dcc62e2458bd74a) )
	ROM_LOAD16_BYTE( "5003-c5.bin", 0x2000000, 0x800000, CRC(c7c1ae50) SHA1(f54f5be7513a5ce2f01ab107a2b26f6a9ee1f2a9) )
	ROM_LOAD16_BYTE( "5003-c6.bin", 0x2000001, 0x800000, CRC(613197f9) SHA1(6d1fefa1be81b79e251e55a1352544c0298e4674) )
	ROM_LOAD16_BYTE( "5003-c7.bin", 0x3000000, 0x800000, CRC(64ddfe0f) SHA1(361f3f4618009bf6419961266eb9ab5002bef53c) )
	ROM_LOAD16_BYTE( "5003-c8.bin", 0x3000001, 0x800000, CRC(917a1439) SHA1(6f28d1d7c6edee1283f25e632c69204dbebe40af) )
ROM_END

ROM_START( kof2k4mp )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "365mp.p1",  0x000000, 0x100000, CRC(499d739d) SHA1(b6344f49acc68405261592115a3c6c6e298309f5))
	ROM_LOAD16_WORD_SWAP( "k2k4s-p1.bin", 0x100000, 0x400000, CRC(e6c50566) SHA1(cc6a3489a3bfeb4dcc65b6ddae0030f7e66fbabe))

	NEO_SFIX_128K( "365mp.s1", CRC(f5f10e6f) SHA1(ab9d390785e03561f6b32f6c66fad2b2e9a5d996))

	NEO_BIOS_AUDIO_128K( "5008-m1.bin", CRC(5a47d9ad) SHA1(0197737934653acc6c97221660d789e9914f3578) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "365mp.v1", 0x000000, 0x400000, CRC(8991f6e9) SHA1(ce5afc0169c142d7f98111afbc60b3a9a2e17256) )
	ROM_LOAD( "365mp.v2", 0x400000, 0x400000, CRC(511e4d2f) SHA1(28190ec86ac2169ab6fad80635ed13cfcf430c65) )
	ROM_LOAD( "365mp.v3", 0x800000, 0x400000, CRC(1dd8b53a) SHA1(9aa84f145ba07f5f3c3b3fb682eb8a8ab1500b4c) )
	ROM_LOAD( "365mp.v4", 0xc00000, 0x400000, CRC(63bb5462) SHA1(afc6a085e25bd006f26e16beda4244bc8bc19bb8) )

	ROM_REGION( 0x4000000, "sprites", 0 )

	ROM_LOAD16_BYTE( "k2k4s-c4.bin", 0x0000000, 0x800000, CRC(7a050288) SHA1(55a20c5b01e11a859f096af3f8e09986025d288f) )
	ROM_LOAD16_BYTE( "k2k4s-c8.bin", 0x0000001, 0x800000, CRC(e924afcf) SHA1(651e974f7339d2cdcfa58c5398013197a0525b77) )
	ROM_LOAD16_BYTE( "265d.c3", 0x1000000, 0x800000, CRC(959fad0b) SHA1(63AB83DDC5F688DC8165A7FF8D262DF3FCD942A2) )
	ROM_LOAD16_BYTE( "265d.c4", 0x1000001, 0x800000, CRC(efe6a468) SHA1(2A414285E48AA948B5B0D4A9333BAB083B5FB853) )
	ROM_LOAD16_BYTE( "265d.c5", 0x2000000, 0x800000, CRC(74bba7c6) SHA1(E01ADC7A4633BC0951B9B4F09ABC07D728E9A2D9) )
	ROM_LOAD16_BYTE( "265d.c6", 0x2000001, 0x800000, CRC(e20d2216) SHA1(5D28EEA7B581E780B78F391A8179F1678EE0D9A5) )
	ROM_LOAD16_BYTE( "k2k4s-c1.bin", 0x3000000, 0x800000, CRC(fa705b2b) SHA1(f314c66876589601806352484dd8e45bc41be692) )
	ROM_LOAD16_BYTE( "k2k4s-c5.bin", 0x3000001, 0x800000, CRC(2c912ff9) SHA1(b624a625ea3e221808b7ea43fb0b1a51d8c1853e) )
ROM_END

ROM_START( kof2k4ru )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "365ru.p1",  0x000000, 0x100000, CRC(69100ad2) SHA1(36a818fb6fbe8433df89187dcf171058128f4f22) )
	ROM_LOAD16_WORD_SWAP( "365ru.p2",  0x100000, 0x400000, CRC(c6b895e0) SHA1(e0080f4bb268253f0605a48c361b6c8088e173b7) )

	NEO_SFIX_128K( "365ru.s1", CRC(fbfa1079) SHA1(af6d779cf0b74c765812d0ca1aab31412adb0136) )

	NEO_BIOS_AUDIO_128K( "5008-m1.bin", CRC(5a47d9ad) SHA1(0197737934653acc6c97221660d789e9914f3578) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "365mp.v1", 0x000000, 0x400000, CRC(8991f6e9) SHA1(ce5afc0169c142d7f98111afbc60b3a9a2e17256) )
	ROM_LOAD( "365mp.v2", 0x400000, 0x400000, CRC(511e4d2f) SHA1(28190ec86ac2169ab6fad80635ed13cfcf430c65) )
	ROM_LOAD( "365mp.v3", 0x800000, 0x400000, CRC(1dd8b53a) SHA1(9aa84f145ba07f5f3c3b3fb682eb8a8ab1500b4c) )
	ROM_LOAD( "365mp.v4", 0xc00000, 0x400000, CRC(63bb5462) SHA1(afc6a085e25bd006f26e16beda4244bc8bc19bb8) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "365ru.c1", 0x0000000, 0x800000, CRC(c55d7733) SHA1(3837f178788c78dcf7b0a4fbab3d62bfe0b41f9a) )
	ROM_LOAD16_BYTE( "365ru.c2", 0x0000001, 0x800000, CRC(d89b45c9) SHA1(31d7ad16534839821f68db07b28dd564fe5c13c3) )
	ROM_LOAD16_BYTE( "365ru.c3", 0x1000000, 0x800000, CRC(e5074eea) SHA1(387ef21d58b416126b95843bac1a0b6cc346818f) )
	ROM_LOAD16_BYTE( "365ru.c4", 0x1000001, 0x800000, CRC(f6eb1ff2) SHA1(77cb493b9e75d42c204a9a6c052a813c2730e44f) )
	ROM_LOAD16_BYTE( "365ru.c5", 0x2000000, 0x800000, CRC(11126545) SHA1(4ae58848c8a6701c9cfcd60e6674e8fb7491c0c0) )
	ROM_LOAD16_BYTE( "365ru.c6", 0x2000001, 0x800000, CRC(d225bb9b) SHA1(ee627dab6aeebfb1af9dbdc315a927245243817c) )
	ROM_LOAD16_BYTE( "365ru.c7", 0x3000000, 0x800000, CRC(750a7a2b) SHA1(3ef7688eedc3fcb9cef55306055b838f60a96285) )
	ROM_LOAD16_BYTE( "365ru.c8", 0x3000001, 0x800000, CRC(aa21b917) SHA1(12f256f2a54246b1ed604ae4dcaa1af6e48a7b1f) )
ROM_END

ROM_START( kof2k4se1 ) // also known as kofse2k4
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "365se1.p2",    0x000000, 0x100000, CRC(5f482757) SHA1(0c2cba7fc6256e62eb7464306036784703c35a70) )
	ROM_LOAD16_WORD_SWAP( "k2k4s-p1.bin", 0x100000, 0x400000, CRC(e6c50566) SHA1(cc6a3489a3bfeb4dcc65b6ddae0030f7e66fbabe) )

	NEO_SFIX_128K( "k2k4s-s1.bin", CRC(a3c9b2d8) SHA1(1472d2cbd7bb73e84824ecf773924007e6117e77) )

	NEO_BIOS_AUDIO_128K( "5008-m1.bin", CRC(5a47d9ad) SHA1(0197737934653acc6c97221660d789e9914f3578) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "365mp.v1", 0x000000, 0x400000, CRC(8991f6e9) SHA1(ce5afc0169c142d7f98111afbc60b3a9a2e17256) )
	ROM_LOAD( "365mp.v2", 0x400000, 0x400000, CRC(511e4d2f) SHA1(28190ec86ac2169ab6fad80635ed13cfcf430c65) )
	ROM_LOAD( "365mp.v3", 0x800000, 0x400000, CRC(1dd8b53a) SHA1(9aa84f145ba07f5f3c3b3fb682eb8a8ab1500b4c) )
	ROM_LOAD( "365mp.v4", 0xc00000, 0x400000, CRC(63bb5462) SHA1(afc6a085e25bd006f26e16beda4244bc8bc19bb8) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "k2k4s-c4.bin", 0x0000000, 0x800000, CRC(7a050288) SHA1(55a20c5b01e11a859f096af3f8e09986025d288f) )
	ROM_LOAD16_BYTE( "k2k4s-c8.bin", 0x0000001, 0x800000, CRC(e924afcf) SHA1(651e974f7339d2cdcfa58c5398013197a0525b77) )
	ROM_LOAD16_BYTE( "265d.c3",      0x1000000, 0x800000, CRC(959fad0b) SHA1(63ab83ddc5f688dc8165a7ff8d262df3fcd942a2) )
	ROM_LOAD16_BYTE( "265d.c4",      0x1000001, 0x800000, CRC(efe6a468) SHA1(2a414285e48aa948b5b0d4a9333bab083b5fb853) )
	ROM_LOAD16_BYTE( "265d.c5",      0x2000000, 0x800000, CRC(74bba7c6) SHA1(e01adc7a4633bc0951b9b4f09abc07d728e9a2d9) )
	ROM_LOAD16_BYTE( "265d.c6",      0x2000001, 0x800000, CRC(e20d2216) SHA1(5d28eea7b581e780b78f391a8179f1678ee0d9a5) )
	ROM_LOAD16_BYTE( "k2k4s-c1.bin", 0x3000000, 0x800000, CRC(fa705b2b) SHA1(f314c66876589601806352484dd8e45bc41be692) )
	ROM_LOAD16_BYTE( "k2k4s-c5.bin", 0x3000001, 0x800000, CRC(2c912ff9) SHA1(b624a625ea3e221808b7ea43fb0b1a51d8c1853e) )
ROM_END

ROM_START( kof2k4se2 ) // also known as kof2004, same as kof2k4se1 except for 2nd program rom
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "365se1.p2", 0x000000, 0x100000, CRC(5f482757) SHA1(0c2cba7fc6256e62eb7464306036784703c35a70) )
	ROM_LOAD16_WORD_SWAP( "365se2.p1", 0x100000, 0x400000, CRC(698679a7) SHA1(2bf3a7a7423141685ecd36c266139a97bac0a69c) )

	NEO_SFIX_128K( "k2k4s-s1.bin", CRC(a3c9b2d8) SHA1(1472d2cbd7bb73e84824ecf773924007e6117e77) )

	NEO_BIOS_AUDIO_128K( "5008-m1.bin", CRC(5a47d9ad) SHA1(0197737934653acc6c97221660d789e9914f3578) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "365mp.v1", 0x000000, 0x400000, CRC(8991f6e9) SHA1(ce5afc0169c142d7f98111afbc60b3a9a2e17256) )
	ROM_LOAD( "365mp.v2", 0x400000, 0x400000, CRC(511e4d2f) SHA1(28190ec86ac2169ab6fad80635ed13cfcf430c65) )
	ROM_LOAD( "365mp.v3", 0x800000, 0x400000, CRC(1dd8b53a) SHA1(9aa84f145ba07f5f3c3b3fb682eb8a8ab1500b4c) )
	ROM_LOAD( "365mp.v4", 0xc00000, 0x400000, CRC(63bb5462) SHA1(afc6a085e25bd006f26e16beda4244bc8bc19bb8) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "k2k4s-c4.bin", 0x0000000, 0x800000, CRC(7a050288) SHA1(55a20c5b01e11a859f096af3f8e09986025d288f) )
	ROM_LOAD16_BYTE( "k2k4s-c8.bin", 0x0000001, 0x800000, CRC(e924afcf) SHA1(651e974f7339d2cdcfa58c5398013197a0525b77) )
	ROM_LOAD16_BYTE( "265d.c3",      0x1000000, 0x800000, CRC(959fad0b) SHA1(63ab83ddc5f688dc8165a7ff8d262df3fcd942a2) )
	ROM_LOAD16_BYTE( "265d.c4",      0x1000001, 0x800000, CRC(efe6a468) SHA1(2a414285e48aa948b5b0d4a9333bab083b5fb853) )
	ROM_LOAD16_BYTE( "265d.c5",      0x2000000, 0x800000, CRC(74bba7c6) SHA1(e01adc7a4633bc0951b9b4f09abc07d728e9a2d9) )
	ROM_LOAD16_BYTE( "265d.c6",      0x2000001, 0x800000, CRC(e20d2216) SHA1(5d28eea7b581e780b78f391a8179f1678ee0d9a5) )
	ROM_LOAD16_BYTE( "k2k4s-c1.bin", 0x3000000, 0x800000, CRC(fa705b2b) SHA1(f314c66876589601806352484dd8e45bc41be692) )
	ROM_LOAD16_BYTE( "k2k4s-c5.bin", 0x3000001, 0x800000, CRC(2c912ff9) SHA1(b624a625ea3e221808b7ea43fb0b1a51d8c1853e) )
ROM_END

ROM_START( kof2k4seb ) /* Portuguese edition */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "365seb.p1", 0x000000, 0x100000, CRC(3dda9add) SHA1(de75ab82ecdd9612b47051a502bfbe4b80c20688) )
	ROM_LOAD16_WORD_SWAP( "365seb.p2", 0x100000, 0x400000, CRC(ed63d10b) SHA1(0991adc15d9335ce429ab0f4e1c20f198c6c0a94) )

	NEO_SFIX_128K( "365seb.s1", CRC(f1b5d31a) SHA1(d111dd7b68fc4a921c0ab19bec40338dd3a88092) )

	NEO_BIOS_AUDIO_128K( "5008-m1.bin", CRC(5a47d9ad) SHA1(0197737934653acc6c97221660d789e9914f3578) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "k2k4s-v2.bin", 0x000000, 0x800000, CRC(e4ddfb3f) SHA1(eb8220ab01c16cf9244b7f3f9912bec0db561b85) )
	ROM_LOAD( "k2k4s-v1.bin", 0x800000, 0x800000, CRC(b887d287) SHA1(f593a5722df6f6fac023d189a739a117e976bb2f) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "k2k4s-c4.bin", 0x0000000, 0x800000, CRC(7a050288) SHA1(55a20c5b01e11a859f096af3f8e09986025d288f) )
	ROM_LOAD16_BYTE( "k2k4s-c8.bin", 0x0000001, 0x800000, CRC(e924afcf) SHA1(651e974f7339d2cdcfa58c5398013197a0525b77) )
	ROM_LOAD16_BYTE( "265d.c3", 0x1000000, 0x800000, CRC(959fad0b) SHA1(63AB83DDC5F688DC8165A7FF8D262DF3FCD942A2) )
	ROM_LOAD16_BYTE( "265d.c4", 0x1000001, 0x800000, CRC(efe6a468) SHA1(2A414285E48AA948B5B0D4A9333BAB083B5FB853) )
	ROM_LOAD16_BYTE( "265d.c5", 0x2000000, 0x800000, CRC(74bba7c6) SHA1(E01ADC7A4633BC0951B9B4F09ABC07D728E9A2D9) )
	ROM_LOAD16_BYTE( "265d.c6", 0x2000001, 0x800000, CRC(e20d2216) SHA1(5D28EEA7B581E780B78F391A8179F1678EE0D9A5) )
	ROM_LOAD16_BYTE( "k2k4s-c1.bin", 0x3000000, 0x800000, CRC(fa705b2b) SHA1(f314c66876589601806352484dd8e45bc41be692) )
	ROM_LOAD16_BYTE( "k2k4s-c5.bin", 0x3000001, 0x800000, CRC(2c912ff9) SHA1(b624a625ea3e221808b7ea43fb0b1a51d8c1853e) )
ROM_END

ROM_START( kof2k4spl )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "365spl.p1",  0x000000, 0x100000, CRC(388c5cba) SHA1(a9dbb3cbe622f8d7c28079883d54665da522dea9))
	ROM_LOAD16_WORD_SWAP( "k2k4s-p1.bin",  0x100000, 0x400000, CRC(e6c50566) SHA1(cc6a3489a3bfeb4dcc65b6ddae0030f7e66fbabe))

	NEO_SFIX_128K( "365spl.s1", CRC(348686dd) SHA1(676d83b98cc0b923ef4997c04cecaf74b4ef1687))

	NEO_BIOS_AUDIO_128K( "5008-m1.bin", CRC(5a47d9ad) SHA1(0197737934653acc6c97221660d789e9914f3578) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "365mp.v1", 0x000000, 0x400000, CRC(8991f6e9) SHA1(ce5afc0169c142d7f98111afbc60b3a9a2e17256) )
	ROM_LOAD( "365mp.v2", 0x400000, 0x400000, CRC(511e4d2f) SHA1(28190ec86ac2169ab6fad80635ed13cfcf430c65) )
	ROM_LOAD( "365mp.v3", 0x800000, 0x400000, CRC(1dd8b53a) SHA1(9aa84f145ba07f5f3c3b3fb682eb8a8ab1500b4c) )
	ROM_LOAD( "365mp.v4", 0xc00000, 0x400000, CRC(63bb5462) SHA1(afc6a085e25bd006f26e16beda4244bc8bc19bb8) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "k2k4s-c4.bin", 0x0000000, 0x800000, CRC(7a050288) SHA1(55a20c5b01e11a859f096af3f8e09986025d288f) )
	ROM_LOAD16_BYTE( "k2k4s-c8.bin", 0x0000001, 0x800000, CRC(e924afcf) SHA1(651e974f7339d2cdcfa58c5398013197a0525b77) )
	ROM_LOAD16_BYTE( "265d.c3", 0x1000000, 0x800000, CRC(959fad0b) SHA1(63AB83DDC5F688DC8165A7FF8D262DF3FCD942A2) )
	ROM_LOAD16_BYTE( "265d.c4", 0x1000001, 0x800000, CRC(efe6a468) SHA1(2A414285E48AA948B5B0D4A9333BAB083B5FB853) )
	ROM_LOAD16_BYTE( "265d.c5", 0x2000000, 0x800000, CRC(74bba7c6) SHA1(E01ADC7A4633BC0951B9B4F09ABC07D728E9A2D9) )
	ROM_LOAD16_BYTE( "265d.c6", 0x2000001, 0x800000, CRC(e20d2216) SHA1(5D28EEA7B581E780B78F391A8179F1678EE0D9A5) )
	ROM_LOAD16_BYTE( "k2k4s-c1.bin", 0x3000000, 0x800000, CRC(fa705b2b) SHA1(f314c66876589601806352484dd8e45bc41be692) )
	ROM_LOAD16_BYTE( "k2k4s-c5.bin", 0x3000001, 0x800000, CRC(2c912ff9) SHA1(b624a625ea3e221808b7ea43fb0b1a51d8c1853e) )
ROM_END

ROM_START( kof2k8uni ) // hack of kof10th
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "366.p1", 0x000000, 0x400000, CRC(966210bf) SHA1(9f86f29dbfe7ac951485908a20a6ce120ebdeb5f) )
	ROM_LOAD16_WORD_SWAP( "366.p2", 0x400000, 0x400000, CRC(ae5f00f7) SHA1(807cbd02cdba320c7cf32c915a663338d7a89252) )

	NEO_SFIX_128K( "366.s1", CRC(e57b5757) SHA1(d3dbb83c3d8b9860361b36496bfdc95220b8b75f) )

	NEO_BIOS_AUDIO_128K( "kf10-m1.bin", CRC(f6fab859) SHA1(0184aa1394b9f9946d610278b53b846020dd88dc) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "kf10-v1.bin", 0x000000, 0x800000, CRC(0fc9a58d) SHA1(9d79ef00e2c2abd9f29af5521c2fbe5798bf336f) )
	ROM_LOAD( "kf10-v2.bin", 0x800000, 0x800000, CRC(b8c475a4) SHA1(10caf9c69927a223445d2c4b147864c02ce520a8) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "366.c1", 0x0000000, 0x400000, CRC(ea774fb8) SHA1(01ce6330716046b591c606b5d016dd5e57fa007b) )
	ROM_LOAD16_BYTE( "366.c2", 0x0000001, 0x400000, CRC(6f497789) SHA1(8c8573ea191d29f0d250901ebf0116a41e184c78) )
	ROM_LOAD16_BYTE( "kf10-c1b.bin", 0x0800000, 0x400000, CRC(b5abfc28) SHA1(eabf60992bb3485c95330065294071ec155bfe7c) )
	ROM_LOAD16_BYTE( "kf10-c2b.bin", 0x0800001, 0x400000, CRC(6cc4c6e1) SHA1(be824a944e745ee18efdc45c81fd496a4d624b9c) )
	ROM_LOAD16_BYTE( "kf10-c3a.bin", 0x1000000, 0x400000, CRC(5b3d4a16) SHA1(93ac1cd7739100f8c32732644f81f2a19837b131) )
	ROM_LOAD16_BYTE( "kf10-c4a.bin", 0x1000001, 0x400000, CRC(c6f3419b) SHA1(340c17a73aeb7bf8a6209f8459e6f00000075b50) )
	ROM_LOAD16_BYTE( "kf10-c3b.bin", 0x1800000, 0x400000, CRC(9d2bba19) SHA1(5ebbd0af3f83a60e33c8ccb743e3d5f5a96f1273) )
	ROM_LOAD16_BYTE( "kf10-c4b.bin", 0x1800001, 0x400000, CRC(5a4050cb) SHA1(8fd2291f349efa1ed5cd37ad4e273b60fe831a77) )
	ROM_LOAD16_BYTE( "kf10-c5a.bin", 0x2000000, 0x400000, CRC(a289d1e1) SHA1(50c7d7ebde6e118a01036cc3e40827fcd9f0d3fd) )
	ROM_LOAD16_BYTE( "kf10-c6a.bin", 0x2000001, 0x400000, CRC(e6494b5d) SHA1(18e064b9867ae0b0794065f8dbefd486620419db) )
	ROM_LOAD16_BYTE( "kf10-c5b.bin", 0x2800000, 0x400000, CRC(404fff02) SHA1(56d1b32c87ea4885e49264e8b21846e465a20e1f) )
	ROM_LOAD16_BYTE( "kf10-c6b.bin", 0x2800001, 0x400000, CRC(f2ccfc9e) SHA1(69db7fac7023785ab94ea711a72dbc2826cfe1a3) )
	ROM_LOAD16_BYTE( "kf10-c7a.bin", 0x3000000, 0x400000, CRC(be79c5a8) SHA1(ded3c5eb3571647f50533eb682c2675372ace3fb) )
	ROM_LOAD16_BYTE( "kf10-c8a.bin", 0x3000001, 0x400000, CRC(a5952ca4) SHA1(76dbb3cb45ce5a4beffa1ed29491204fc6617e42) )
	ROM_LOAD16_BYTE( "366.c7", 0x3800000, 0x400000, CRC(1b6f3bde) SHA1(5e1222197f5a09837930cc34713667dc1644c02a) )
	ROM_LOAD16_BYTE( "366.c8", 0x3800001, 0x400000, CRC(113555e3) SHA1(52b48e182d23422492d95c95de4c86b1d30864e0) )
ROM_END

ROM_START( kof10thu ) 
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "363u.p1", 0x600000, 0x100000, CRC(dd135fb6) SHA1(4e85814a44ee9fee9760048dd6d6fd2b66521bb1) )
	ROM_CONTINUE( 0x100000, 0x500000 )
	ROM_CONTINUE( 0x000000, 0x100000 )
	ROM_CONTINUE( 0x700000, 0x100000 )

	NEO_SFIX_128K( "363u.s1", CRC(b22ba74f) SHA1(3ba9e9d4b95fef9bf35f76e9d4fb6e1a36aeee5a) )

	NEO_BIOS_AUDIO_128K( "kf10-m1.bin", CRC(f6fab859) SHA1(0184aa1394b9f9946d610278b53b846020dd88dc) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "kf10-v1.bin", 0x000000, 0x800000, CRC(0fc9a58d) SHA1(9d79ef00e2c2abd9f29af5521c2fbe5798bf336f) )
	ROM_LOAD( "kf10-v2.bin", 0x800000, 0x800000, CRC(b8c475a4) SHA1(10caf9c69927a223445d2c4b147864c02ce520a8) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "kf10-c1a.bin", 0x0000000, 0x400000, CRC(3bbc0364) SHA1(e8aa7ff82f151ce1db56f259377b64cceef85af0) )
	ROM_LOAD16_BYTE( "kf10-c2a.bin", 0x0000001, 0x400000, CRC(91230075) SHA1(d9098e05a7ba6008661147b6bf8bc2f494b8b72b) )
	ROM_LOAD16_BYTE( "kf10-c1b.bin", 0x0800000, 0x400000, CRC(b5abfc28) SHA1(eabf60992bb3485c95330065294071ec155bfe7c) )
	ROM_LOAD16_BYTE( "kf10-c2b.bin", 0x0800001, 0x400000, CRC(6cc4c6e1) SHA1(be824a944e745ee18efdc45c81fd496a4d624b9c) )
	ROM_LOAD16_BYTE( "kf10-c3a.bin", 0x1000000, 0x400000, CRC(5b3d4a16) SHA1(93ac1cd7739100f8c32732644f81f2a19837b131) )
	ROM_LOAD16_BYTE( "kf10-c4a.bin", 0x1000001, 0x400000, CRC(c6f3419b) SHA1(340c17a73aeb7bf8a6209f8459e6f00000075b50) )
	ROM_LOAD16_BYTE( "kf10-c3b.bin", 0x1800000, 0x400000, CRC(9d2bba19) SHA1(5ebbd0af3f83a60e33c8ccb743e3d5f5a96f1273) )
	ROM_LOAD16_BYTE( "kf10-c4b.bin", 0x1800001, 0x400000, CRC(5a4050cb) SHA1(8fd2291f349efa1ed5cd37ad4e273b60fe831a77) )
	ROM_LOAD16_BYTE( "kf10-c5a.bin", 0x2000000, 0x400000, CRC(a289d1e1) SHA1(50c7d7ebde6e118a01036cc3e40827fcd9f0d3fd) )
	ROM_LOAD16_BYTE( "kf10-c6a.bin", 0x2000001, 0x400000, CRC(e6494b5d) SHA1(18e064b9867ae0b0794065f8dbefd486620419db) )
	ROM_LOAD16_BYTE( "kf10-c5b.bin", 0x2800000, 0x400000, CRC(404fff02) SHA1(56d1b32c87ea4885e49264e8b21846e465a20e1f) )
	ROM_LOAD16_BYTE( "kf10-c6b.bin", 0x2800001, 0x400000, CRC(f2ccfc9e) SHA1(69db7fac7023785ab94ea711a72dbc2826cfe1a3) )
	ROM_LOAD16_BYTE( "kf10-c7a.bin", 0x3000000, 0x400000, CRC(be79c5a8) SHA1(ded3c5eb3571647f50533eb682c2675372ace3fb) )
	ROM_LOAD16_BYTE( "kf10-c8a.bin", 0x3000001, 0x400000, CRC(a5952ca4) SHA1(76dbb3cb45ce5a4beffa1ed29491204fc6617e42) )
	ROM_LOAD16_BYTE( "kf10-c7b.bin", 0x3800000, 0x400000, CRC(3fdb3542) SHA1(7d2050752a2064cd6729f483a0da93808e2c6033) )
	ROM_LOAD16_BYTE( "kf10-c8b.bin", 0x3800001, 0x400000, CRC(661b7a52) SHA1(0ae2ad2389134892f156337332b77adade3ddad1) )
ROM_END

ROM_START( kof10thub )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "363ub.p1", 0x000000, 0x800000, CRC(814eb1b2) SHA1(529825948f17fffa6d3a55a0d9e7ba6c06b79649) )

	NEO_SFIX_128K( "363ub.s1", CRC(f5f91fc8) SHA1(f64516d7b500bdeddbe64962330cb612c11b8b84) )

	NEO_BIOS_AUDIO_128K( "kf10-m1.bin", CRC(f6fab859) SHA1(0184aa1394b9f9946d610278b53b846020dd88dc) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "kf10-v1.bin", 0x000000, 0x800000, CRC(0fc9a58d) SHA1(9d79ef00e2c2abd9f29af5521c2fbe5798bf336f) )
	ROM_LOAD( "kf10-v2.bin", 0x800000, 0x800000, CRC(b8c475a4) SHA1(10caf9c69927a223445d2c4b147864c02ce520a8) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "363ud.c1", 0x0000000, 0x800000, CRC(2491af91) SHA1(e3e237e50395dc985c564867046ad202bc744d37) )
	ROM_LOAD16_BYTE( "363ud.c2", 0x0000001, 0x800000, CRC(47ff1d91) SHA1(7d6ade9409af2c64114ed5836ccf9f50c7ebac69) )
	ROM_LOAD16_BYTE( "265d.c3", 0x1000000, 0x800000, CRC(959fad0b) SHA1(63AB83DDC5F688DC8165A7FF8D262DF3FCD942A2) )
	ROM_LOAD16_BYTE( "265d.c4", 0x1000001, 0x800000, CRC(efe6a468) SHA1(2A414285E48AA948B5B0D4A9333BAB083B5FB853) )
	ROM_LOAD16_BYTE( "265d.c5", 0x2000000, 0x800000, CRC(74bba7c6) SHA1(E01ADC7A4633BC0951B9B4F09ABC07D728E9A2D9) )
	ROM_LOAD16_BYTE( "265d.c6", 0x2000001, 0x800000, CRC(e20d2216) SHA1(5D28EEA7B581E780B78F391A8179F1678EE0D9A5) )
	ROM_LOAD16_BYTE( "265d.c7", 0x3000000, 0x800000, CRC(8a5b561c) SHA1(A19697D4C2CC8EDEBC669C95AE1DB4C8C2A70B2C) )
	ROM_LOAD16_BYTE( "265d.c8", 0x3000001, 0x800000, CRC(bef667a3) SHA1(D5E8BC185DCF63343D129C31D2DDAB9F723F1A12) )
ROM_END

ROM_START( kof10thud )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "363ud.p1", 0x000000, 0x800000, CRC(acbe077a) SHA1(7d3b1ce4e06021f26dd1a7d97b03975f4ed17c24) )

	NEO_SFIX_128K( "363u.s1", CRC(b22ba74f) SHA1(3ba9e9d4b95fef9bf35f76e9d4fb6e1a36aeee5a) )

	NEO_BIOS_AUDIO_128K( "kf10-m1.bin", CRC(f6fab859) SHA1(0184aa1394b9f9946d610278b53b846020dd88dc) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "kf10-v1.bin", 0x000000, 0x800000, CRC(0fc9a58d) SHA1(9d79ef00e2c2abd9f29af5521c2fbe5798bf336f) )
	ROM_LOAD( "kf10-v2.bin", 0x800000, 0x800000, CRC(b8c475a4) SHA1(10caf9c69927a223445d2c4b147864c02ce520a8) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "363ud.c1", 0x0000000, 0x800000, CRC(2491af91) SHA1(e3e237e50395dc985c564867046ad202bc744d37) )
	ROM_LOAD16_BYTE( "363ud.c2", 0x0000001, 0x800000, CRC(47ff1d91) SHA1(7d6ade9409af2c64114ed5836ccf9f50c7ebac69) )
	ROM_LOAD16_BYTE( "265d.c3", 0x1000000, 0x800000, CRC(959fad0b) SHA1(63AB83DDC5F688DC8165A7FF8D262DF3FCD942A2) )
	ROM_LOAD16_BYTE( "265d.c4", 0x1000001, 0x800000, CRC(efe6a468) SHA1(2A414285E48AA948B5B0D4A9333BAB083B5FB853) )
	ROM_LOAD16_BYTE( "265d.c5", 0x2000000, 0x800000, CRC(74bba7c6) SHA1(E01ADC7A4633BC0951B9B4F09ABC07D728E9A2D9) )
	ROM_LOAD16_BYTE( "265d.c6", 0x2000001, 0x800000, CRC(e20d2216) SHA1(5D28EEA7B581E780B78F391A8179F1678EE0D9A5) )
	ROM_LOAD16_BYTE( "265d.c7", 0x3000000, 0x800000, CRC(8a5b561c) SHA1(A19697D4C2CC8EDEBC669C95AE1DB4C8C2A70B2C) )
	ROM_LOAD16_BYTE( "265d.c8", 0x3000001, 0x800000, CRC(bef667a3) SHA1(D5E8BC185DCF63343D129C31D2DDAB9F723F1A12) )
ROM_END

ROM_START( kogd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "361d.p1", 0x000000, 0x100000, CRC(58F20940) SHA1(693819ff606b7c7b27400586f34073625445c412) )
	ROM_LOAD16_WORD_SWAP( "232-p2.sp2", 0x100000, 0x400000, CRC(158b23f6) SHA1(9744620a70513490aaf9c5eda33e5ec31222be19) )

	NEO_SFIX_128K( "361d.s1", CRC(EC690592) SHA1(a5af2880778a1904dd6c6006be769ea36b15dae3) )

	NEO_BIOS_AUDIO_128K( "232-m1.m1", CRC(45348747) SHA1(ed77cbae2b208d1177a9f5f6e8cd57070e90b65b) )

	ROM_REGION( 0xc00000, "ymsnd", 0 )
	ROM_LOAD( "232-v1.v1", 0x000000, 0x400000, CRC(22a2b5b5) SHA1(ebdbc977332e6d93e266755000b43857e0082965) )
	ROM_LOAD( "232-v2.v2", 0x400000, 0x400000, CRC(2304e744) SHA1(98d283e2bcc9291a53f52afd35ef76dfb0828432) )
	ROM_LOAD( "232-v3.v3", 0x800000, 0x400000, CRC(759eb954) SHA1(54e77c4e9e6b89458e59824e478ddc33a9c72655) )

	ROM_REGION( 0x2800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "361d.c1", 0x0000000, 0x800000, CRC(8E964A75) SHA1(e7611d7908ca056f4b3c0ae2c4da8f6809db4556) )
	ROM_LOAD16_BYTE( "361d.c2", 0x0000001, 0x800000, CRC(D102DE17) SHA1(e98f33a4d16ebda6cf369b92480d4306c780cf8b) )
	ROM_LOAD16_BYTE( "232-c3.c3", 0x1000000, 0x800000, CRC(581d6618) SHA1(14d3124a08ded59f86932c6b28e1a4e48c564ccd) )
	ROM_LOAD16_BYTE( "232-c4.c4", 0x1000001, 0x800000, CRC(49bb1e68) SHA1(f769c1bd1b019521111ff3f0d22c63cb1f2640ef) )
	ROM_LOAD16_BYTE( "361d.c5", 0x2000000, 0x400000, CRC(C2698BE3) SHA1(0b1d414549947f6c29ebc71057aef96634656f32) )
	ROM_LOAD16_BYTE( "361d.c6", 0x2000001, 0x400000, CRC(B057DB30) SHA1(2f342f03848f3f553bc70b2dbee2cc388a344a06) )
ROM_END

ROM_START( kogf )
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "361f.p1", 0x000000, 0x200000, CRC(65dc181d) SHA1(663e1296fd808b3fc14fc94c3b82f9097db455e3) )
	ROM_LOAD16_WORD_SWAP( "232-p2.sp2",  0x200000, 0x400000, CRC(158b23f6) SHA1(9744620a70513490aaf9c5eda33e5ec31222be19) )

	NEO_SFIX_128K( "361f.s1", CRC(a5a76377) SHA1(e35f195dcd0a4ab156d6d52e8cc8fddddc602fc1) )

	NEO_BIOS_AUDIO_128K( "232-m1.m1", CRC(45348747) SHA1(ed77cbae2b208d1177a9f5f6e8cd57070e90b65b) )

	ROM_REGION( 0xc00000, "ymsnd", 0 )
	ROM_LOAD( "232-v1.v1", 0x000000, 0x400000, CRC(22a2b5b5) SHA1(ebdbc977332e6d93e266755000b43857e0082965) )
	ROM_LOAD( "232-v2.v2", 0x400000, 0x400000, CRC(2304e744) SHA1(98d283e2bcc9291a53f52afd35ef76dfb0828432) )
	ROM_LOAD( "232-v3.v3", 0x800000, 0x400000, CRC(759eb954) SHA1(54e77c4e9e6b89458e59824e478ddc33a9c72655) )

	ROM_REGION( 0x2800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "5232-c1a.bin", 0x0000000, 0x800000, CRC(4eab9b0a) SHA1(a6f6b755215a3f41474e0a76b5463303a522c2d3) )
	ROM_LOAD16_BYTE( "5232-c2a.bin", 0x0000001, 0x800000, CRC(697f8fd0) SHA1(5784464c2357ccef8e6e79b6298843fc3d13b39c) )
	ROM_LOAD16_BYTE( "5232-c1b.bin", 0x1000000, 0x800000, CRC(1143fdf3) SHA1(9dc5fe9a3b7599380db62095880e2d6f237a41bd) )
	ROM_LOAD16_BYTE( "5232-c2b.bin", 0x1000001, 0x800000, CRC(ea82cf8f) SHA1(3d9ab64b69cecd6b3950839ac2c6d151ad66dcf8) )
	ROM_LOAD16_BYTE( "5232-c3.bin", 0x2000000, 0x400000, CRC(abd1be07) SHA1(857eb68bbee4538770bbfa77aaa540d61ab0abcd) )
	ROM_LOAD16_BYTE( "5232-c4.bin", 0x2000001, 0x400000, CRC(d2bd967b) SHA1(c494e0a98e127d37ca360a28accc167fa50fb626) )
ROM_END

ROM_START( kogplus )
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "361plus.p1", 0x000000, 0x200000, CRC(0338f453) SHA1(01ea5ca6cc632d732a539542dc163bbafb071b88) )
	ROM_LOAD16_WORD_SWAP( "kf97-p2p.bin", 0x200000, 0x400000, CRC(5502b020) SHA1(37c48198d8b3798910a44075782cd1a20b687b4a) )

	NEO_SFIX_128K( "361plus.s1", CRC(6271e9ba) SHA1(5bc94426e916d0ad16b6660bfc2b9e21f717fa32) )

	NEO_BIOS_AUDIO_128K( "232-m1.m1", CRC(45348747) SHA1(ed77cbae2b208d1177a9f5f6e8cd57070e90b65b) )

	ROM_REGION( 0xc00000, "ymsnd", 0 )
	ROM_LOAD( "232-v1.v1", 0x000000, 0x400000, CRC(22a2b5b5) SHA1(ebdbc977332e6d93e266755000b43857e0082965) )
	ROM_LOAD( "232-v2.v2", 0x400000, 0x400000, CRC(2304e744) SHA1(98d283e2bcc9291a53f52afd35ef76dfb0828432) )
	ROM_LOAD( "232-v3.v3", 0x800000, 0x400000, CRC(759eb954) SHA1(54e77c4e9e6b89458e59824e478ddc33a9c72655) )

	ROM_REGION( 0x2800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "5232-c1a.bin", 0x0000000, 0x800000, CRC(4eab9b0a) SHA1(a6f6b755215a3f41474e0a76b5463303a522c2d3) )
	ROM_LOAD16_BYTE( "5232-c2a.bin", 0x0000001, 0x800000, CRC(697f8fd0) SHA1(5784464c2357ccef8e6e79b6298843fc3d13b39c) )
	ROM_LOAD16_BYTE( "5232-c1b.bin", 0x1000000, 0x800000, CRC(1143fdf3) SHA1(9dc5fe9a3b7599380db62095880e2d6f237a41bd) )
	ROM_LOAD16_BYTE( "5232-c2b.bin", 0x1000001, 0x800000, CRC(ea82cf8f) SHA1(3d9ab64b69cecd6b3950839ac2c6d151ad66dcf8) )
	ROM_LOAD16_BYTE( "5232-c3.bin",  0x2000000, 0x400000, CRC(abd1be07) SHA1(857eb68bbee4538770bbfa77aaa540d61ab0abcd) )
	ROM_LOAD16_BYTE( "5232-c4.bin",  0x2000001, 0x400000, CRC(d2bd967b) SHA1(c494e0a98e127d37ca360a28accc167fa50fb626) )
ROM_END

ROM_START( kogplusf )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "361plusf.p1", 0x000000, 0x100000, CRC(24d0684b) SHA1(e2bf117e8dcad6e058cc0d2702f9e373e9aebb29) )
	ROM_LOAD16_WORD_SWAP( "kf97-p2p.bin", 0x100000, 0x400000, CRC(5502b020) SHA1(37c48198d8b3798910a44075782cd1a20b687b4a) )

	NEO_SFIX_128K( "361plusf.s1", CRC(3e6d76ec) SHA1(f16912d6d199f1c917efa3caece52e5730dfeb5f) )

	NEO_BIOS_AUDIO_128K( "232-m1.m1", CRC(45348747) SHA1(ed77cbae2b208d1177a9f5f6e8cd57070e90b65b) )

	ROM_REGION( 0xc00000, "ymsnd", 0 )
	ROM_LOAD( "232-v1.v1", 0x000000, 0x400000, CRC(22a2b5b5) SHA1(ebdbc977332e6d93e266755000b43857e0082965) )
	ROM_LOAD( "232-v2.v2", 0x400000, 0x400000, CRC(2304e744) SHA1(98d283e2bcc9291a53f52afd35ef76dfb0828432) )
	ROM_LOAD( "232-v3.v3", 0x800000, 0x400000, CRC(759eb954) SHA1(54e77c4e9e6b89458e59824e478ddc33a9c72655) )

	ROM_REGION( 0x2800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "361d.c1", 0x0000000, 0x800000, CRC(8E964A75) SHA1(e7611d7908ca056f4b3c0ae2c4da8f6809db4556) )
	ROM_LOAD16_BYTE( "361d.c2", 0x0000001, 0x800000, CRC(D102DE17) SHA1(e98f33a4d16ebda6cf369b92480d4306c780cf8b) )
	ROM_LOAD16_BYTE( "232-c3.c3", 0x1000000, 0x800000, CRC(581d6618) SHA1(14d3124a08ded59f86932c6b28e1a4e48c564ccd) )
	ROM_LOAD16_BYTE( "232-c4.c4", 0x1000001, 0x800000, CRC(49bb1e68) SHA1(f769c1bd1b019521111ff3f0d22c63cb1f2640ef) )
	ROM_LOAD16_BYTE( "361d.c5", 0x2000000, 0x400000, CRC(C2698BE3) SHA1(0b1d414549947f6c29ebc71057aef96634656f32) )
	ROM_LOAD16_BYTE( "361d.c6", 0x2000001, 0x400000, CRC(B057DB30) SHA1(2f342f03848f3f553bc70b2dbee2cc388a344a06) )
ROM_END



GAME( 2003, cthd2k3b,   neogeo,   neogeo_noslot,     neogeo, neogeo_noslot_state,     cthd2003,  ROT0, "HunterX Hacker", "Crouching Tiger Hidden Dragon 2003 (Add Char)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, ct2k3eh,    cthd2k3b, neogeo_noslot,     neogeo, neogeo_noslot_state,     cthd2003,  ROT0, "Fighters Kim and HunterX Hacker", "Crouching Tiger Hidden Dragon 2003 (Add Char - Pow hack)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, ct2k3k3,    cthd2k3b, neogeo_noslot,     neogeo, neogeo_noslot_state,     cthd2003,  ROT0, "Jason/K3", "Crouching Tiger Hidden Dragon 2003 Remix v1.2 (Diff Move - 030823)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, ct2k3k3o,   cthd2k3b, neogeo_noslot,     neogeo, neogeo_noslot_state,     cthd2003,  ROT0, "Jason/K3", "Crouching Tiger Hidden Dragon 2003 Remix (Diff Move - 030818)", MACHINE_SUPPORTS_SAVE )
GAME( 2004, kof2k4mp,   kof2002,  neogeo_noslot,     neogeo, neogeo_noslot_state,     kof2k4se,  ROT0, "hack", "Kof Special Edition 2004 Magic PLUS", MACHINE_SUPPORTS_SAVE )
GAME( 2010, kof2k4ru,   kof2002,  neogeo_noslot,     neogeo, neogeo_state,            neogeo,    ROT0, "MVS Hacks PSP", "Kof Special Edition 2004 REMIX ULTRA V2.6F", MACHINE_SUPPORTS_SAVE )
GAME( 2004, kof2k4se1,  kof2002,  neogeo_noslot,     neogeo, neogeo_noslot_state,     kof2k4se,  ROT0, "hack", "Kof Special Edition 2004 (hack 1)", MACHINE_SUPPORTS_SAVE )
GAME( 2004, kof2k4se2,  kof2002,  neogeo_noslot,     neogeo, neogeo_noslot_state,     kof2k4se,  ROT0, "hack", "Kof Special Edition 2004 (hack 2)", MACHINE_SUPPORTS_SAVE )
GAME( 2004, kof2k4seb,  kof2002,  neogeo_noslot,     neogeo, neogeo_state,            neogeo,    ROT0, "Dragon Co.", "Kof Special Edition 2004 (portuguese)", MACHINE_SUPPORTS_SAVE )
GAME( 2004, kof2k4spl,  kof2002,  neogeo_noslot,     neogeo, neogeo_noslot_state,     kof2k4se,  ROT0, "hack", "Kof Special Edition 2004 Plus", MACHINE_SUPPORTS_SAVE )
GAME( 2008, kof2k8uni,  kof2002,  neogeo_noslot,     neogeo, neogeo_state,            neogeo,    ROT0, "hack", "Kof 10th Anniversary 2008 Unique", MACHINE_SUPPORTS_SAVE )
GAME( 2005, kof10thu,   kof2002,  neogeo_noslot,     neogeo, neogeo_hbmame,           kof10thu,  ROT0, "hack", "Kof 10th Anniversary UNIQUE (bootleg)", MACHINE_SUPPORTS_SAVE )
GAME( 2005, kof10thub,  kof2002,  neogeo_noslot,     neogeo, neogeo_state,            neogeo,    ROT0, "hack", "Kof 10th Anniversary UNIQUE (portuguese edition)", MACHINE_SUPPORTS_SAVE )
GAME( 2005, kof10thud,  kof2002,  neogeo_noslot,     neogeo, neogeo_state,            neogeo,    ROT0, "hack", "Kof 10th Anniversary UNIQUE (decrypted, bootleg)", MACHINE_SUPPORTS_SAVE )
GAME( 2005, kogd,       kof97,    hbmame_kog,        neogeo, neogeo_hbmame,           kogd,      ROT0, "hack", "King of Gladiator (fully decrypted)", MACHINE_SUPPORTS_SAVE )
GAME( 1997, kogf,       kof97,    neogeo_noslot_kog, neogeo, neogeo_noslot_kog_state, kog,       ROT0, "Zxbdragon / Ryu", "King of Gladiator (Fixed Edition by Zxbdragon & Ryu)", MACHINE_SUPPORTS_SAVE )
GAME( 1997, kogplus,    kof97,    neogeo_noslot_kog, neogeo, neogeo_noslot_kog_state, kog,       ROT0, "hack", "King of Gladiator PLUS", MACHINE_SUPPORTS_SAVE )
GAME( 1997, kogplusf,   kof97,    hbmame_kog,        neogeo, neogeo_hbmame,           kogd,      ROT0, "Zxbdragon / Ryu", "King of Gladiator PLUS (Fixed Edition by Zxbdragon & Ryu)", MACHINE_SUPPORTS_SAVE )
///GAME( 2004, kf2k4pls,   kof2002,  neogeo_noslot,   neogeo, neogeo_state,   kf2k4pls, ROT0, "hack", "Kof2004 Special Edition Plus", MACHINE_SUPPORTS_SAVE )
///GAME( 2004, kof10thd,   kof2002,  neogeo_noslot,   neogeo, neogeo_state,   kof10thd, ROT0, "hack", "Kof 10th Anniversary (Fully Decrypted)", MACHINE_SUPPORTS_SAVE )
