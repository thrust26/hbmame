// license:BSD-3-Clause
// copyright-holders:Robbbert



DRIVER_INIT_MEMBER( neogeo_hbmame, kof2003b )
{
	DRIVER_INIT_CALL(neogeo);
	m_bootleg_prot->kf2k3bl_install_protection(m_maincpu, m_banked_cart, cpuregion, cpuregion_size);
	m_bootleg_prot->neogeo_bootleg_sx_decrypt(fix_region, fix_region_size, 1);
}

DRIVER_INIT_MEMBER( neogeo_hbmame, kof2003d )
{
	DRIVER_INIT_CALL(neogeo);
	m_sprgen->m_fixed_layer_bank_type = 2;
	m_cmc_prot->neogeo_cmc50_m1_decrypt(audiocrypt_region, audiocrypt_region_size, audiocpu_region, audio_region_size);
	m_pcm2_prot->neo_pcm2_swap(ym_region, ym_region_size, 5);
	m_cmc_prot->neogeo_sfix_decrypt(spr_region, spr_region_size, fix_region, fix_region_size);
}

DRIVER_INIT_MEMBER( neogeo_hbmame, kof2k3br )
{
	DRIVER_INIT_CALL(neogeo);
	m_sprgen->m_fixed_layer_bank_type = 2;
	m_cmc_prot->neogeo_sfix_decrypt(spr_region, spr_region_size, fix_region, fix_region_size);
}

DRIVER_INIT_MEMBER( neogeo_hbmame, kof2k3d )
{
	DRIVER_INIT_CALL(neogeo);
	m_sprgen->m_fixed_layer_bank_type = 2;
	m_pvc_prot->kof2003_decrypt_68k(cpuregion, cpuregion_size);
	m_pvc_prot->install_pvc_protection(m_maincpu, m_banked_cart);
	m_cmc_prot->neogeo_cmc50_m1_decrypt(audiocrypt_region, audiocrypt_region_size, audiocpu_region, audio_region_size);
	m_pcm2_prot->neo_pcm2_swap(ym_region, ym_region_size, 5);
	m_cmc_prot->neogeo_sfix_decrypt(spr_region, spr_region_size, fix_region, fix_region_size);
}

DRIVER_INIT_MEMBER( neogeo_hbmame, kof2k3hd )
{
	DRIVER_INIT_CALL(neogeo);
	m_sprgen->m_fixed_layer_bank_type = 2;
	m_pvc_prot->kof2003h_decrypt_68k(cpuregion, cpuregion_size);  // different to kof2k3d
	m_pvc_prot->install_pvc_protection(m_maincpu, m_banked_cart);
	m_cmc_prot->neogeo_cmc50_m1_decrypt(audiocrypt_region, audiocrypt_region_size, audiocpu_region, audio_region_size);
	m_pcm2_prot->neo_pcm2_swap(ym_region, ym_region_size, 5);
	m_cmc_prot->neogeo_sfix_decrypt(spr_region, spr_region_size, fix_region, fix_region_size);
}

DRIVER_INIT_MEMBER( neogeo_hbmame, kof2k3pcd ) // decrypted C & decrypted Bios
{
	DRIVER_INIT_CALL(neogeo);
	m_sprgen->m_fixed_layer_bank_type = 2;
	m_pvc_prot->kf2k3pcb_decrypt_68k(cpuregion, cpuregion_size);
	m_pvc_prot->install_pvc_protection(m_maincpu, m_banked_cart);
	m_cmc_prot->neogeo_cmc50_m1_decrypt(audiocrypt_region, audiocrypt_region_size, audiocpu_region, audio_region_size);

	// Extra m1 decryption
	int i;
	UINT8* rom = memregion("audiocpu")->base();
	for (i = 0; i < 0x90000; i++)
		rom[i] = BITSWAP8(rom[i], 5, 6, 1, 4, 3, 0, 7, 2);

	m_pcm2_prot->neo_pcm2_swap(ym_region, ym_region_size, 5);
	neogeo_noslot_state::kf2k3pcb_decrypt_s1data();
	m_maincpu->space(AS_PROGRAM).install_rom(0xc00000, 0xc7ffff, 0, 0x080000, memregion("mainbios")->base());  // 512k bios
}



ROM_START( kof2003d )
	ROM_REGION( 0x700000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "271d.p0", 0x000000, 0x100000, CRC(7c2aee16) SHA1(b4373569c4a26829a93759ba6917879518f2fb20) )
	ROM_LOAD16_WORD_SWAP( "271b.p1", 0x100000, 0x400000, CRC(92ed6ee3) SHA1(5e7e21eb40dfcc453ba73808760d5ddedd49c58a) )
	ROM_LOAD16_WORD_SWAP( "271d.p2", 0x500000, 0x200000, CRC(0d0a5861) SHA1(823dd3d11574a42f98588a6d1f9bb5d721f34be2) )

	NEO_SFIX_MT_512K

	NEO_BIOS_AUDIO_ENCRYPTED_512K( "271-m1c.m1", CRC(f5515629) SHA1(7516bf1b0207a3c8d41dc30c478f8d8b1f71304b) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "271-v1c.v1", 0x000000, 0x800000, CRC(ffa3f8c7) SHA1(7cf4a933973ca23b7f87c81151d8659e6ec4bd20) )
	ROM_LOAD( "271-v2c.v2", 0x800000, 0x800000, CRC(5382c7d1) SHA1(1bf999705eda80ba1e7b0d6bdd010d9bfb18bd76) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "271b.c1", 0x0000000, 0x800000, CRC(e42fc226) SHA1(1cd9364993e141facdcdd53ec2277df7b275d8a7) )
	ROM_LOAD16_BYTE( "271b.c2", 0x0000001, 0x800000, CRC(1b5e3b58) SHA1(0eb254477a9479541291e43e415310852a0f0bed) )
	ROM_LOAD16_BYTE( "271b.c3", 0x1000000, 0x800000, CRC(d334fdd9) SHA1(1efe30b4f56a55e25ab518cf6999de797b5e407c) )
	ROM_LOAD16_BYTE( "271b.c4", 0x1000001, 0x800000, CRC(0d457699) SHA1(ec73d0c9fc7094d0ac6c0986a6e07cde25893e57) )
	ROM_LOAD16_BYTE( "271b.c5", 0x2000000, 0x800000, CRC(8a91aae4) SHA1(802f4baacf801646be1ef686e105b2e867a6a5df) )
	ROM_LOAD16_BYTE( "271b.c6", 0x2000001, 0x800000, CRC(9f8674b8) SHA1(65964f40b2227d020023fb436579927e65807dcd) )
	ROM_LOAD16_BYTE( "271d.c7", 0x3000000, 0x800000, CRC(8ee6b43c) SHA1(c78b749c7c8e1d8ab8335b96da03764cc8e9eb21) )
	ROM_LOAD16_BYTE( "271d.c8", 0x3000001, 0x800000, CRC(6d8d2d60) SHA1(841698eead0f7d422937ce2f2329e17c383d90a6) )
ROM_END

ROM_START( kof2003f )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "271f.p1", 0x000000, 0x400000, CRC(d29a0d06) SHA1(a5ba68ceac0b4bceb0c37d65844d96835eb244e4) )
	ROM_LOAD16_WORD_SWAP( "271f.p2", 0x400000, 0x400000, CRC(95477dd4) SHA1(3a57befa3e0772b2989ba5b76afd95f3aed1936b) )

	NEO_SFIX_128K( "271f.s1", CRC(7c7829aa) SHA1(22f8d38d1d0891295d0593741d9477fbe6b4f48c) )

	NEO_BIOS_AUDIO_512K( "271br.m1", CRC(0e86af8f) SHA1(769102b67bb1a699cfa5674d66cdb46ae633cb65) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "271f.v1", 0x000000, 0x1000000, CRC(2964f36e) SHA1(bfc52f81354eb57e27acb3b80fe1547b9e070293) )

	ROM_REGION( 0x6000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "271pcd.c1", 0x0000000, 0x1000000, CRC(c29acd28) SHA1(8a10409c5a9ad95fa9b56e94c14f1b96101fb179) )
	ROM_LOAD16_BYTE( "271pcd.c2", 0x0000001, 0x1000000, CRC(328e80b1) SHA1(c7f8069488be1a88a2ea03718b6a131f5c96bd3f) )
	ROM_LOAD16_BYTE( "271pcd.c3", 0x2000000, 0x1000000, CRC(020a11f1) SHA1(85cfae76234f72b0039ebc02f931bb2a9c10b1af) )
	ROM_LOAD16_BYTE( "271pcd.c4", 0x2000001, 0x1000000, CRC(991b5ed2) SHA1(99c4c470bc9cb388773e27de6df4a16803fc7b45) )
	ROM_LOAD16_BYTE( "271pcd.c5", 0x4000000, 0x1000000, CRC(c2de8b66) SHA1(40c2ea48fc20d470163a9dbb40c0276fc4cfceb9) )
	ROM_LOAD16_BYTE( "271pcd.c6", 0x4000001, 0x1000000, CRC(3ff750db) SHA1(714f14a2eb2df6f25d10a6b6aff4b3adfbc7a5dc) )
ROM_END

ROM_START( kof2003rebh ) // no watchdog
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "271rebh.p1", 0x000000, 0x800000, CRC(cd7c9f42) SHA1(d99f25a0d7c640c8594aef25e818ee017845de90) )

	NEO_SFIX_128K( "271rebh.s1", CRC(e146f5cc) SHA1(1ca3e36ec87b40c8eaa7c92d1bf7a066fdb0b26c) )

	NEO_BIOS_AUDIO_128K( "271rebh.m1", CRC(396e17cd) SHA1(b2962aef711883402e67fcfb475265abe68e2cba) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "271b.v1", 0x000000, 0x400000, CRC(d2b8aa5e) SHA1(498f0556c1de56822141f8043f1ce20444f4ed0a) )
	ROM_LOAD( "271b.v2", 0x400000, 0x400000, CRC(71956ee2) SHA1(a890941e60db358cf45b58909f4719f4826f3bb1) )
	ROM_LOAD( "271b.v3", 0x800000, 0x400000, CRC(ddbbb199) SHA1(0eea4b064bdb8daa03c354fe0a0aa27c4c665bda) )
	ROM_LOAD( "271b.v4", 0xc00000, 0x400000, CRC(01b90c4f) SHA1(387164aa1995d8c11ed939b3afbc294d86d2e27f) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "271b.c1", 0x0000000, 0x800000, CRC(e42fc226) SHA1(1cd9364993e141facdcdd53ec2277df7b275d8a7) )
	ROM_LOAD16_BYTE( "271b.c2", 0x0000001, 0x800000, CRC(1b5e3b58) SHA1(0eb254477a9479541291e43e415310852a0f0bed) )
	ROM_LOAD16_BYTE( "271b.c3", 0x1000000, 0x800000, CRC(d334fdd9) SHA1(1efe30b4f56a55e25ab518cf6999de797b5e407c) )
	ROM_LOAD16_BYTE( "271b.c4", 0x1000001, 0x800000, CRC(0d457699) SHA1(ec73d0c9fc7094d0ac6c0986a6e07cde25893e57) )
	ROM_LOAD16_BYTE( "271b.c5", 0x2000000, 0x800000, CRC(8a91aae4) SHA1(802f4baacf801646be1ef686e105b2e867a6a5df) )
	ROM_LOAD16_BYTE( "271b.c6", 0x2000001, 0x800000, CRC(9f8674b8) SHA1(65964f40b2227d020023fb436579927e65807dcd) )
	ROM_LOAD16_BYTE( "271b.c7", 0x3000000, 0x800000, CRC(374ea523) SHA1(613827d72c6181f3e08353750c9af0c4dbad020b) )
	ROM_LOAD16_BYTE( "271b.c8", 0x3000001, 0x800000, CRC(75211f4d) SHA1(d82f044e816ee539ff131d9c931200c818d34cd0) )
ROM_END

ROM_START( kof2k3b ) /* The King of Fighters 2003 BOOTLEG - (kof2k3b) - Hack by Gledson01 - (Can choose Kusanagi, Chizuru, Maki, Mukai and Adelheid) */
	ROM_REGION( 0x700000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "271b.p1", 0x100000, 0x400000, CRC(92ed6ee3) SHA1(5e7e21eb40dfcc453ba73808760d5ddedd49c58a) )
	ROM_LOAD16_WORD_SWAP( "271b.p2", 0x500000, 0x200000, CRC(fb01a5b3) SHA1(3c8e92362f8169f5e64d6e1d1fea41edd2e7a6a3) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "271b.s1", CRC(482c48a5) SHA1(27e2f5295a9a838e112be28dafc111893a388a16) )

	NEO_BIOS_AUDIO_128K( "271b.m1", CRC(3a4969ff) SHA1(2fc107a023a82053a8df63025829bcf12cee9610) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "271b.v1", 0x000000, 0x400000, CRC(d2b8aa5e) SHA1(498f0556c1de56822141f8043f1ce20444f4ed0a) )
	ROM_LOAD( "271b.v2", 0x400000, 0x400000, CRC(71956ee2) SHA1(a890941e60db358cf45b58909f4719f4826f3bb1) )
	ROM_LOAD( "271b.v3", 0x800000, 0x400000, CRC(ddbbb199) SHA1(0eea4b064bdb8daa03c354fe0a0aa27c4c665bda) )
	ROM_LOAD( "271b.v4", 0xc00000, 0x400000, CRC(01b90c4f) SHA1(387164aa1995d8c11ed939b3afbc294d86d2e27f) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "271b.c1", 0x0000000, 0x800000, CRC(e42fc226) SHA1(1cd9364993e141facdcdd53ec2277df7b275d8a7) )
	ROM_LOAD16_BYTE( "271b.c2", 0x0000001, 0x800000, CRC(1b5e3b58) SHA1(0eb254477a9479541291e43e415310852a0f0bed) )
	ROM_LOAD16_BYTE( "271b.c3", 0x1000000, 0x800000, CRC(d334fdd9) SHA1(1efe30b4f56a55e25ab518cf6999de797b5e407c) )
	ROM_LOAD16_BYTE( "271b.c4", 0x1000001, 0x800000, CRC(0d457699) SHA1(ec73d0c9fc7094d0ac6c0986a6e07cde25893e57) )
	ROM_LOAD16_BYTE( "271b.c5", 0x2000000, 0x800000, CRC(8a91aae4) SHA1(802f4baacf801646be1ef686e105b2e867a6a5df) )
	ROM_LOAD16_BYTE( "271b.c6", 0x2000001, 0x800000, CRC(9f8674b8) SHA1(65964f40b2227d020023fb436579927e65807dcd) )
	ROM_LOAD16_BYTE( "271b.c7", 0x3000000, 0x800000, CRC(374ea523) SHA1(613827d72c6181f3e08353750c9af0c4dbad020b) )
	ROM_LOAD16_BYTE( "271b.c8", 0x3000001, 0x800000, CRC(75211f4d) SHA1(d82f044e816ee539ff131d9c931200c818d34cd0) )
ROM_END

ROM_START( kof2k3br )
	ROM_REGION( 0x800000, "maincpu", 0 ) 
	ROM_LOAD16_WORD_SWAP( "271br.p1", 0x000000, 0x800000, CRC(a131786e) SHA1(3754e6361063221138c95c52a3edb3e88a74048a) )

	NEO_SFIX_MT_512K

	NEO_BIOS_AUDIO_512K( "271br.m1", CRC(0e86af8f) SHA1(769102b67bb1a699cfa5674d66cdb46ae633cb65) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	//ROM_LOAD( "271bs4.v1", 0x000000, 0x800000, CRC(dd6c6a85) SHA1(e32b16d0b716a4f3b95868457347303d020147fb) )
	//ROM_LOAD( "271bs4.v2", 0x800000, 0x800000, CRC(0e84f8c1) SHA1(28c964fe89c800b445d3a65c965de32b4e504726) )
	ROM_LOAD( "271b.v1", 0x000000, 0x400000, CRC(d2b8aa5e) SHA1(498f0556c1de56822141f8043f1ce20444f4ed0a) )
	ROM_LOAD( "271b.v2", 0x400000, 0x400000, CRC(71956ee2) SHA1(a890941e60db358cf45b58909f4719f4826f3bb1) )
	ROM_LOAD( "271b.v3", 0x800000, 0x400000, CRC(ddbbb199) SHA1(0eea4b064bdb8daa03c354fe0a0aa27c4c665bda) )
	ROM_LOAD( "271b.v4", 0xc00000, 0x400000, CRC(01b90c4f) SHA1(387164aa1995d8c11ed939b3afbc294d86d2e27f) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "271b.c1", 0x0000000, 0x800000, CRC(e42fc226) SHA1(1cd9364993e141facdcdd53ec2277df7b275d8a7) )
	ROM_LOAD16_BYTE( "271b.c2", 0x0000001, 0x800000, CRC(1b5e3b58) SHA1(0eb254477a9479541291e43e415310852a0f0bed) )
	ROM_LOAD16_BYTE( "271b.c3", 0x1000000, 0x800000, CRC(d334fdd9) SHA1(1efe30b4f56a55e25ab518cf6999de797b5e407c) )
	ROM_LOAD16_BYTE( "271b.c4", 0x1000001, 0x800000, CRC(0d457699) SHA1(ec73d0c9fc7094d0ac6c0986a6e07cde25893e57) )
	ROM_LOAD16_BYTE( "271b.c5", 0x2000000, 0x800000, CRC(8a91aae4) SHA1(802f4baacf801646be1ef686e105b2e867a6a5df) )
	ROM_LOAD16_BYTE( "271b.c6", 0x2000001, 0x800000, CRC(9f8674b8) SHA1(65964f40b2227d020023fb436579927e65807dcd) )
	ROM_LOAD16_BYTE( "271br.c7", 0x3000000, 0x800000, CRC(f3d81b6e) SHA1(62bf0c9d1d9f7a016d125df64c8328e01e003e43) )
	ROM_LOAD16_BYTE( "271br.c8", 0x3000001, 0x800000, CRC(5310c6dc) SHA1(e9cb89392fa5604d3ac3ba58acdb1b739d1267be) )
ROM_END

ROM_START( kof2k3bs4 )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "271bs4.p1", 0x000000, 0x800000, CRC(536d02e7) SHA1(5432c79d3808da3bbf47521a0e2f0ed3f9e7a435) )

	NEO_SFIX_128K( "271bs4.s1", CRC(8b176a55) SHA1(600a0c9c2e5b17dc2c345756d71a08a9c4a3f26e) )

	NEO_BIOS_AUDIO_512K( "271br.m1", CRC(0e86af8f) SHA1(769102b67bb1a699cfa5674d66cdb46ae633cb65) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "271bs4.v1", 0x000000, 0x800000, CRC(dd6c6a85) SHA1(e32b16d0b716a4f3b95868457347303d020147fb) )
	ROM_LOAD( "271bs4.v2", 0x800000, 0x800000, CRC(0e84f8c1) SHA1(28c964fe89c800b445d3a65c965de32b4e504726) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "271b.c1", 0x0000000, 0x800000, CRC(e42fc226) SHA1(1cd9364993e141facdcdd53ec2277df7b275d8a7) )
	ROM_LOAD16_BYTE( "271b.c2", 0x0000001, 0x800000, CRC(1b5e3b58) SHA1(0eb254477a9479541291e43e415310852a0f0bed) )
	ROM_LOAD16_BYTE( "271b.c3", 0x1000000, 0x800000, CRC(d334fdd9) SHA1(1efe30b4f56a55e25ab518cf6999de797b5e407c) )
	ROM_LOAD16_BYTE( "271b.c4", 0x1000001, 0x800000, CRC(0d457699) SHA1(ec73d0c9fc7094d0ac6c0986a6e07cde25893e57) )
	ROM_LOAD16_BYTE( "271b.c5", 0x2000000, 0x800000, CRC(8a91aae4) SHA1(802f4baacf801646be1ef686e105b2e867a6a5df) )
	ROM_LOAD16_BYTE( "271b.c6", 0x2000001, 0x800000, CRC(9f8674b8) SHA1(65964f40b2227d020023fb436579927e65807dcd) )
	ROM_LOAD16_BYTE( "271bs4.c7", 0x3000000, 0x800000, CRC(0ff993d7) SHA1(c7d6ce90b84d566dcee85dba5591f8f394fcf032) )
	ROM_LOAD16_BYTE( "271bs4.c8", 0x3000001, 0x800000, CRC(22e36002) SHA1(bb3a9e1ded0af2db058cfbe773ed5c1a1b4e888a) )
ROM_END

ROM_START( kof2k3d )
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD32_WORD_SWAP( "271-p1c.p1", 0x000000, 0x400000, CRC(530ecc14) SHA1(812cf7e9902af3f5e9e330b7c05c2171b139ad2b) )
	ROM_LOAD32_WORD_SWAP( "271-p2c.p2", 0x000002, 0x400000, CRC(fd568da9) SHA1(46364906a1e81dc251117e91a1a7b43af1373ada) )
	ROM_LOAD16_WORD_SWAP( "271-p3c.p3", 0x800000, 0x100000, CRC(aec5b4a9) SHA1(74087f785590eda5898ce146029818f86ced42b6) )

	NEO_SFIX_MT_512K

	NEO_BIOS_AUDIO_ENCRYPTED_512K( "271-m1c.m1", CRC(f5515629) SHA1(7516bf1b0207a3c8d41dc30c478f8d8b1f71304b) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "271-v1c.v1", 0x000000, 0x800000, CRC(ffa3f8c7) SHA1(7cf4a933973ca23b7f87c81151d8659e6ec4bd20) )
	ROM_LOAD( "271-v2c.v2", 0x800000, 0x800000, CRC(5382c7d1) SHA1(1bf999705eda80ba1e7b0d6bdd010d9bfb18bd76) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "271d.c1", 0x0000000, 0x800000, CRC(e42fc226) SHA1(1cd9364993e141facdcdd53ec2277df7b275d8a7) )
	ROM_LOAD16_BYTE( "271d.c2", 0x0000001, 0x800000, CRC(1b5e3b58) SHA1(0eb254477a9479541291e43e415310852a0f0bed) )
	ROM_LOAD16_BYTE( "271d.c3", 0x1000000, 0x800000, CRC(d334fdd9) SHA1(1efe30b4f56a55e25ab518cf6999de797b5e407c) )
	ROM_LOAD16_BYTE( "271d.c4", 0x1000001, 0x800000, CRC(0d457699) SHA1(ec73d0c9fc7094d0ac6c0986a6e07cde25893e57) )
	ROM_LOAD16_BYTE( "271d.c5", 0x2000000, 0x800000, CRC(8a91aae4) SHA1(802f4baacf801646be1ef686e105b2e867a6a5df) )
	ROM_LOAD16_BYTE( "271d.c6", 0x2000001, 0x800000, CRC(9f8674b8) SHA1(65964f40b2227d020023fb436579927e65807dcd) )
	ROM_LOAD16_BYTE( "271d.c7", 0x3000000, 0x800000, CRC(8ee6b43c) SHA1(c78b749c7c8e1d8ab8335b96da03764cc8e9eb21) )
	ROM_LOAD16_BYTE( "271d.c8", 0x3000001, 0x800000, CRC(6d8d2d60) SHA1(841698eead0f7d422937ce2f2329e17c383d90a6) )
ROM_END

ROM_START( kof2k3evo )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "271evo.p1", 0x000000, 0x800000, CRC(ce221039) SHA1(755feabb4a3b2b02f72bd2747b13051fe3d0116c) )

	NEO_SFIX_128K( "271evo.s1", CRC(2849fbfb) SHA1(1c46decf77c9802589bbd445344f6e3b9e82afd2) )

	NEO_BIOS_AUDIO_128K( "271rebh.m1", CRC(396e17cd) SHA1(b2962aef711883402e67fcfb475265abe68e2cba) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "271b.v1", 0x000000, 0x400000, CRC(d2b8aa5e) SHA1(498f0556c1de56822141f8043f1ce20444f4ed0a) )
	ROM_LOAD( "271b.v2", 0x400000, 0x400000, CRC(71956ee2) SHA1(a890941e60db358cf45b58909f4719f4826f3bb1) )
	ROM_LOAD( "271b.v3", 0x800000, 0x400000, CRC(ddbbb199) SHA1(0eea4b064bdb8daa03c354fe0a0aa27c4c665bda) )
	ROM_LOAD( "271b.v4", 0xc00000, 0x400000, CRC(01b90c4f) SHA1(387164aa1995d8c11ed939b3afbc294d86d2e27f) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "271b.c1", 0x0000000, 0x800000, CRC(e42fc226) SHA1(1cd9364993e141facdcdd53ec2277df7b275d8a7) )
	ROM_LOAD16_BYTE( "271b.c2", 0x0000001, 0x800000, CRC(1b5e3b58) SHA1(0eb254477a9479541291e43e415310852a0f0bed) )
	ROM_LOAD16_BYTE( "271b.c3", 0x1000000, 0x800000, CRC(d334fdd9) SHA1(1efe30b4f56a55e25ab518cf6999de797b5e407c) )
	ROM_LOAD16_BYTE( "271b.c4", 0x1000001, 0x800000, CRC(0d457699) SHA1(ec73d0c9fc7094d0ac6c0986a6e07cde25893e57) )
	ROM_LOAD16_BYTE( "271b.c5", 0x2000000, 0x800000, CRC(8a91aae4) SHA1(802f4baacf801646be1ef686e105b2e867a6a5df) )
	ROM_LOAD16_BYTE( "271b.c6", 0x2000001, 0x800000, CRC(9f8674b8) SHA1(65964f40b2227d020023fb436579927e65807dcd) )
	ROM_LOAD16_BYTE( "271b.c7", 0x3000000, 0x800000, CRC(374ea523) SHA1(613827d72c6181f3e08353750c9af0c4dbad020b) )
	ROM_LOAD16_BYTE( "271b.c8", 0x3000001, 0x800000, CRC(75211f4d) SHA1(d82f044e816ee539ff131d9c931200c818d34cd0) )
ROM_END

ROM_START( kof2k3gc ) /* The King of Fighters 2003 BOOTLEG - (kof2k3gc) - Colour fix by Gledson01 - (Character colour change for Terry (4P), Athena (3P), Ash (3P), Leona (3P), K' (4P) and King (2P) ) */
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "271gc.p1", 0x100000, 0x400000, CRC(ba621186) SHA1(061e072fb5baaf8454f362a9a81bf51a324cc73d) )
	ROM_LOAD16_WORD_SWAP( "271gc.p2", 0x500000, 0x200000, CRC(5d3d8bb3) SHA1(7f2341f14ca12ff5721eb038b3496228a1f34b60) )
	ROM_IGNORE( 0x100000 )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "271b.s1", CRC(482c48a5) SHA1(27e2f5295a9a838e112be28dafc111893a388a16) )

	NEO_BIOS_AUDIO_128K( "271b.m1", CRC(3a4969ff) SHA1(2fc107a023a82053a8df63025829bcf12cee9610) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "271b.v1", 0x000000, 0x400000, CRC(d2b8aa5e) SHA1(498f0556c1de56822141f8043f1ce20444f4ed0a) )
	ROM_LOAD( "271b.v2", 0x400000, 0x400000, CRC(71956ee2) SHA1(a890941e60db358cf45b58909f4719f4826f3bb1) )
	ROM_LOAD( "271b.v3", 0x800000, 0x400000, CRC(ddbbb199) SHA1(0eea4b064bdb8daa03c354fe0a0aa27c4c665bda) )
	ROM_LOAD( "271b.v4", 0xc00000, 0x400000, CRC(01b90c4f) SHA1(387164aa1995d8c11ed939b3afbc294d86d2e27f) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "271b.c1", 0x0000000, 0x800000, CRC(e42fc226) SHA1(1cd9364993e141facdcdd53ec2277df7b275d8a7) )
	ROM_LOAD16_BYTE( "271b.c2", 0x0000001, 0x800000, CRC(1b5e3b58) SHA1(0eb254477a9479541291e43e415310852a0f0bed) )
	ROM_LOAD16_BYTE( "271b.c3", 0x1000000, 0x800000, CRC(d334fdd9) SHA1(1efe30b4f56a55e25ab518cf6999de797b5e407c) )
	ROM_LOAD16_BYTE( "271b.c4", 0x1000001, 0x800000, CRC(0d457699) SHA1(ec73d0c9fc7094d0ac6c0986a6e07cde25893e57) )
	ROM_LOAD16_BYTE( "271b.c5", 0x2000000, 0x800000, CRC(8a91aae4) SHA1(802f4baacf801646be1ef686e105b2e867a6a5df) )
	ROM_LOAD16_BYTE( "271b.c6", 0x2000001, 0x800000, CRC(9f8674b8) SHA1(65964f40b2227d020023fb436579927e65807dcd) )
	ROM_LOAD16_BYTE( "271b.c7", 0x3000000, 0x800000, CRC(374ea523) SHA1(613827d72c6181f3e08353750c9af0c4dbad020b) )
	ROM_LOAD16_BYTE( "271b.c8", 0x3000001, 0x800000, CRC(75211f4d) SHA1(d82f044e816ee539ff131d9c931200c818d34cd0) )
ROM_END

ROM_START( kof2k3hd ) // decrypted version of kof2003h
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD32_WORD_SWAP( "271-p1k.p1", 0x000000, 0x400000, CRC(d0d0ae3e) SHA1(538d054ac50c91694fbbfefcce548b063713e14e) )
	ROM_LOAD32_WORD_SWAP( "271-p2k.p2", 0x000002, 0x400000, CRC(fb3f79d9) SHA1(f253d10e732d6e23ae82d74ac9269d21f69ddb4d) )
	ROM_LOAD16_WORD_SWAP( "271-p3k.p3", 0x800000, 0x100000, CRC(232702ad) SHA1(6045046027dac1cbd4cbd14b5c1ece522bc6197f) )

	NEO_SFIX_MT_512K

	NEO_BIOS_AUDIO_ENCRYPTED_512K( "271-m1k.m1", CRC(48d9affe) SHA1(68f01560b91bbada39001ce01bdeeed5c9bb29f2) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "271-v1c.v1", 0x000000, 0x800000, CRC(ffa3f8c7) SHA1(7cf4a933973ca23b7f87c81151d8659e6ec4bd20) )
	ROM_LOAD( "271-v2c.v2", 0x800000, 0x800000, CRC(5382c7d1) SHA1(1bf999705eda80ba1e7b0d6bdd010d9bfb18bd76) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "271b.c1", 0x0000000, 0x800000, CRC(e42fc226) SHA1(1cd9364993e141facdcdd53ec2277df7b275d8a7) )
	ROM_LOAD16_BYTE( "271b.c2", 0x0000001, 0x800000, CRC(1b5e3b58) SHA1(0eb254477a9479541291e43e415310852a0f0bed) )
	ROM_LOAD16_BYTE( "271b.c3", 0x1000000, 0x800000, CRC(d334fdd9) SHA1(1efe30b4f56a55e25ab518cf6999de797b5e407c) )
	ROM_LOAD16_BYTE( "271b.c4", 0x1000001, 0x800000, CRC(0d457699) SHA1(ec73d0c9fc7094d0ac6c0986a6e07cde25893e57) )
	ROM_LOAD16_BYTE( "271b.c5", 0x2000000, 0x800000, CRC(8a91aae4) SHA1(802f4baacf801646be1ef686e105b2e867a6a5df) )
	ROM_LOAD16_BYTE( "271b.c6", 0x2000001, 0x800000, CRC(9f8674b8) SHA1(65964f40b2227d020023fb436579927e65807dcd) )
	ROM_LOAD16_BYTE( "271d.c7", 0x3000000, 0x800000, CRC(8ee6b43c) SHA1(c78b749c7c8e1d8ab8335b96da03764cc8e9eb21) )
	ROM_LOAD16_BYTE( "271d.c8", 0x3000001, 0x800000, CRC(6d8d2d60) SHA1(841698eead0f7d422937ce2f2329e17c383d90a6) )
ROM_END

ROM_START( kof2k3pcd )
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD32_WORD_SWAP( "271-p1.p1", 0x000000, 0x400000, CRC(b9da070c) SHA1(1a26325af142a4dd221c336061761468598c4634) )
	ROM_LOAD32_WORD_SWAP( "271-p2.p2", 0x000002, 0x400000, CRC(da3118c4) SHA1(582e4f44f03276adecb7b2848d3b96bf6da57f1e) )
	ROM_LOAD16_WORD_SWAP( "271-p3.p3", 0x800000, 0x100000, CRC(5cefd0d2) SHA1(cddc3164629fed4b6f715e12b109ad35d1009355) )

	ROM_Y_ZOOM
	ROM_REGION( 0x100000, "fixed", ROMREGION_ERASE00 ) /* larger char set */
	ROM_REGION( 0x20000, "fixedbios", 0 )
	ROM_LOAD( "sfix.sfix", 0x000000, 0x20000, CRC(c2ea0cfd) SHA1(fd4a618cdcdbf849374f0a50dd8efe9dbab706c3) )

	ROM_REGION16_BE( 0x80000, "mainbios", 0 )
	ROM_LOAD16_WORD_SWAP( "271pcd.sp1", 0x00000, 0x080000, CRC(e873f1ef) SHA1(e7f7a6084b9d7f4b4f8819ea0fd115b1f2cac2c2) )

	ROM_REGION( 0x80000, "audiocrypt", 0 )
	ROM_LOAD( "271-m1.m1", 0x00000, 0x80000, CRC(d6bcf2bc) SHA1(df78bc95990eb8e8f3638dde6e1876354df7fe84) )
	ROM_REGION( 0x90000, "audiocpu", ROMREGION_ERASEFF )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "271-v1.v1", 0x000000, 0x1000000, CRC(1d96154b) SHA1(1d4e262b0d30cee79a4edc83bb9706023c736668) )

	ROM_REGION( 0x6000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "271pcd.c1", 0x0000000, 0x1000000, CRC(c29acd28) SHA1(8a10409c5a9ad95fa9b56e94c14f1b96101fb179) )
	ROM_LOAD16_BYTE( "271pcd.c2", 0x0000001, 0x1000000, CRC(328e80b1) SHA1(c7f8069488be1a88a2ea03718b6a131f5c96bd3f) )
	ROM_LOAD16_BYTE( "271pcd.c3", 0x2000000, 0x1000000, CRC(020a11f1) SHA1(85cfae76234f72b0039ebc02f931bb2a9c10b1af) )
	ROM_LOAD16_BYTE( "271pcd.c4", 0x2000001, 0x1000000, CRC(991b5ed2) SHA1(99c4c470bc9cb388773e27de6df4a16803fc7b45) )
	ROM_LOAD16_BYTE( "271pcd.c5", 0x4000000, 0x1000000, CRC(c2de8b66) SHA1(40c2ea48fc20d470163a9dbb40c0276fc4cfceb9) )
	ROM_LOAD16_BYTE( "271pcd.c6", 0x4000001, 0x1000000, CRC(3ff750db) SHA1(714f14a2eb2df6f25d10a6b6aff4b3adfbc7a5dc) )
ROM_END

ROM_START( kof2k3ps2 )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "271ps2.p1", 0x000000, 0x800000, CRC(8e66056d) SHA1(8ddbbf66bdcefbae15e9c0597aea846bbcfccadd) )

	NEO_SFIX_128K( "271ps2.s1", CRC(c2e48e98) SHA1(8734c3d1c936aff3d7d1f460b5d211e25a816cc5) )

	NEO_BIOS_AUDIO_512K( "271ps2.m1", CRC(4374cb5c) SHA1(d245a09fcebc8fe59f4af2de2fc30a0871e56d68) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "271bs4.v1", 0x000000, 0x800000, CRC(dd6c6a85) SHA1(e32b16d0b716a4f3b95868457347303d020147fb) )
	ROM_LOAD( "271bs4.v2", 0x800000, 0x800000, CRC(0e84f8c1) SHA1(28c964fe89c800b445d3a65c965de32b4e504726) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "271b.c1", 0x0000000, 0x800000, CRC(e42fc226) SHA1(1cd9364993e141facdcdd53ec2277df7b275d8a7) )
	ROM_LOAD16_BYTE( "271b.c2", 0x0000001, 0x800000, CRC(1b5e3b58) SHA1(0eb254477a9479541291e43e415310852a0f0bed) )
	ROM_LOAD16_BYTE( "271b.c3", 0x1000000, 0x800000, CRC(d334fdd9) SHA1(1efe30b4f56a55e25ab518cf6999de797b5e407c) )
	ROM_LOAD16_BYTE( "271b.c4", 0x1000001, 0x800000, CRC(0d457699) SHA1(ec73d0c9fc7094d0ac6c0986a6e07cde25893e57) )
	ROM_LOAD16_BYTE( "271b.c5", 0x2000000, 0x800000, CRC(8a91aae4) SHA1(802f4baacf801646be1ef686e105b2e867a6a5df) )
	ROM_LOAD16_BYTE( "271b.c6", 0x2000001, 0x800000, CRC(9f8674b8) SHA1(65964f40b2227d020023fb436579927e65807dcd) )
	ROM_LOAD16_BYTE( "271bs4.c7", 0x3000000, 0x800000, CRC(0ff993d7) SHA1(c7d6ce90b84d566dcee85dba5591f8f394fcf032) )
	ROM_LOAD16_BYTE( "271bs4.c8", 0x3000001, 0x800000, CRC(22e36002) SHA1(bb3a9e1ded0af2db058cfbe773ed5c1a1b4e888a) )
ROM_END

ROM_START( kof2k3ryu )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "271ryu.p1", 0x000000, 0x800000, CRC(0e82da28) SHA1(61fd4cf63f804752095f47450e4aac10672bd53f) )

	NEO_SFIX_128K( "271ryu.s1", CRC(d05be6db) SHA1(a523e6b7b8f07e6636043d13626a2286c79de930) )

	NEO_BIOS_AUDIO_512K( "271br.m1", CRC(0e86af8f) SHA1(769102b67bb1a699cfa5674d66cdb46ae633cb65) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "271f.v1", 0x000000, 0x1000000, CRC(2964f36e) SHA1(bfc52f81354eb57e27acb3b80fe1547b9e070293) )

	ROM_REGION( 0x6000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "271pcd.c1", 0x0000000, 0x1000000, CRC(c29acd28) SHA1(8a10409c5a9ad95fa9b56e94c14f1b96101fb179) )
	ROM_LOAD16_BYTE( "271pcd.c2", 0x0000001, 0x1000000, CRC(328e80b1) SHA1(c7f8069488be1a88a2ea03718b6a131f5c96bd3f) )
	ROM_LOAD16_BYTE( "271pcd.c3", 0x2000000, 0x1000000, CRC(020a11f1) SHA1(85cfae76234f72b0039ebc02f931bb2a9c10b1af) )
	ROM_LOAD16_BYTE( "271pcd.c4", 0x2000001, 0x1000000, CRC(991b5ed2) SHA1(99c4c470bc9cb388773e27de6df4a16803fc7b45) )
	ROM_LOAD16_BYTE( "271pcd.c5", 0x4000000, 0x1000000, CRC(c2de8b66) SHA1(40c2ea48fc20d470163a9dbb40c0276fc4cfceb9) )
	ROM_LOAD16_BYTE( "271pcd.c6", 0x4000001, 0x1000000, CRC(3ff750db) SHA1(714f14a2eb2df6f25d10a6b6aff4b3adfbc7a5dc) )
ROM_END

ROM_START( kof2k3sc ) /* The King of Fighters 2003 BOOTLEG - (kof2k3sc) - Colour fix by SHIPDS - (Colour change) */
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "271sc.p1", 0x100000, 0x400000, CRC(ef4ee94e) SHA1(f3b8b9e7279dfc4c04dc5971c323134d8db3b42c) )
	ROM_LOAD16_WORD_SWAP( "271gc.p2", 0x500000, 0x200000, CRC(5d3d8bb3) SHA1(7f2341f14ca12ff5721eb038b3496228a1f34b60) )
	ROM_IGNORE( 0x100000 )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "271b.s1", CRC(482c48a5) SHA1(27e2f5295a9a838e112be28dafc111893a388a16) )

	NEO_BIOS_AUDIO_128K( "271b.m1", CRC(3a4969ff) SHA1(2fc107a023a82053a8df63025829bcf12cee9610) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "271b.v1", 0x000000, 0x400000, CRC(d2b8aa5e) SHA1(498f0556c1de56822141f8043f1ce20444f4ed0a) )
	ROM_LOAD( "271b.v2", 0x400000, 0x400000, CRC(71956ee2) SHA1(a890941e60db358cf45b58909f4719f4826f3bb1) )
	ROM_LOAD( "271b.v3", 0x800000, 0x400000, CRC(ddbbb199) SHA1(0eea4b064bdb8daa03c354fe0a0aa27c4c665bda) )
	ROM_LOAD( "271b.v4", 0xc00000, 0x400000, CRC(01b90c4f) SHA1(387164aa1995d8c11ed939b3afbc294d86d2e27f) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "271b.c1", 0x0000000, 0x800000, CRC(e42fc226) SHA1(1cd9364993e141facdcdd53ec2277df7b275d8a7) )
	ROM_LOAD16_BYTE( "271b.c2", 0x0000001, 0x800000, CRC(1b5e3b58) SHA1(0eb254477a9479541291e43e415310852a0f0bed) )
	ROM_LOAD16_BYTE( "271b.c3", 0x1000000, 0x800000, CRC(d334fdd9) SHA1(1efe30b4f56a55e25ab518cf6999de797b5e407c) )
	ROM_LOAD16_BYTE( "271b.c4", 0x1000001, 0x800000, CRC(0d457699) SHA1(ec73d0c9fc7094d0ac6c0986a6e07cde25893e57) )
	ROM_LOAD16_BYTE( "271b.c5", 0x2000000, 0x800000, CRC(8a91aae4) SHA1(802f4baacf801646be1ef686e105b2e867a6a5df) )
	ROM_LOAD16_BYTE( "271b.c6", 0x2000001, 0x800000, CRC(9f8674b8) SHA1(65964f40b2227d020023fb436579927e65807dcd) )
	ROM_LOAD16_BYTE( "271b.c7", 0x3000000, 0x800000, CRC(374ea523) SHA1(613827d72c6181f3e08353750c9af0c4dbad020b) )
	ROM_LOAD16_BYTE( "271b.c8", 0x3000001, 0x800000, CRC(75211f4d) SHA1(d82f044e816ee539ff131d9c931200c818d34cd0) )
ROM_END

ROM_START( kof2k3tc ) /* The King of Fighters 2003 BOOTLEG - (kof2k3tc) - Colour fix by T.Com - (Character colour change for Kyo (2P/4P), DUOLON (4P), K' (4P) ) */
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "271tc.p1", 0x100000, 0x400000, CRC(0d1a1da9) SHA1(0ba0d11c3bb3c30bc95f9aae181769ea874da096) )
	ROM_LOAD16_WORD_SWAP( "271gc.p2", 0x500000, 0x200000, CRC(5d3d8bb3) SHA1(7f2341f14ca12ff5721eb038b3496228a1f34b60) )
	ROM_IGNORE( 0x100000 )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "271b.s1", CRC(482c48a5) SHA1(27e2f5295a9a838e112be28dafc111893a388a16) )

	NEO_BIOS_AUDIO_128K( "271b.m1", CRC(3a4969ff) SHA1(2fc107a023a82053a8df63025829bcf12cee9610) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "271b.v1", 0x000000, 0x400000, CRC(d2b8aa5e) SHA1(498f0556c1de56822141f8043f1ce20444f4ed0a) )
	ROM_LOAD( "271b.v2", 0x400000, 0x400000, CRC(71956ee2) SHA1(a890941e60db358cf45b58909f4719f4826f3bb1) )
	ROM_LOAD( "271b.v3", 0x800000, 0x400000, CRC(ddbbb199) SHA1(0eea4b064bdb8daa03c354fe0a0aa27c4c665bda) )
	ROM_LOAD( "271b.v4", 0xc00000, 0x400000, CRC(01b90c4f) SHA1(387164aa1995d8c11ed939b3afbc294d86d2e27f) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "271b.c1", 0x0000000, 0x800000, CRC(e42fc226) SHA1(1cd9364993e141facdcdd53ec2277df7b275d8a7) )
	ROM_LOAD16_BYTE( "271b.c2", 0x0000001, 0x800000, CRC(1b5e3b58) SHA1(0eb254477a9479541291e43e415310852a0f0bed) )
	ROM_LOAD16_BYTE( "271b.c3", 0x1000000, 0x800000, CRC(d334fdd9) SHA1(1efe30b4f56a55e25ab518cf6999de797b5e407c) )
	ROM_LOAD16_BYTE( "271b.c4", 0x1000001, 0x800000, CRC(0d457699) SHA1(ec73d0c9fc7094d0ac6c0986a6e07cde25893e57) )
	ROM_LOAD16_BYTE( "271b.c5", 0x2000000, 0x800000, CRC(8a91aae4) SHA1(802f4baacf801646be1ef686e105b2e867a6a5df) )
	ROM_LOAD16_BYTE( "271b.c6", 0x2000001, 0x800000, CRC(9f8674b8) SHA1(65964f40b2227d020023fb436579927e65807dcd) )
	ROM_LOAD16_BYTE( "271b.c7", 0x3000000, 0x800000, CRC(374ea523) SHA1(613827d72c6181f3e08353750c9af0c4dbad020b) )
	ROM_LOAD16_BYTE( "271b.c8", 0x3000001, 0x800000, CRC(75211f4d) SHA1(d82f044e816ee539ff131d9c931200c818d34cd0) )
ROM_END

ROM_START( kof2k3zgf ) /* The King of Fighters 2003 BOOTLEG - (kof2k3zgf) - Colour fix by Zhaolu94 - (Attack cremation green) */
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "271zgf.p1", 0x100000, 0x400000, CRC(9a76d66f) SHA1(4697b521105759d135f859e47940e3696f49506b) )
	ROM_LOAD16_WORD_SWAP( "271gc.p2",  0x500000, 0x200000, CRC(5d3d8bb3) SHA1(7f2341f14ca12ff5721eb038b3496228a1f34b60) )
	ROM_IGNORE( 0x100000 )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "271b.s1", CRC(482c48a5) SHA1(27e2f5295a9a838e112be28dafc111893a388a16) )

	NEO_BIOS_AUDIO_128K( "271b.m1", CRC(3a4969ff) SHA1(2fc107a023a82053a8df63025829bcf12cee9610) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "271b.v1", 0x000000, 0x400000, CRC(d2b8aa5e) SHA1(498f0556c1de56822141f8043f1ce20444f4ed0a) )
	ROM_LOAD( "271b.v2", 0x400000, 0x400000, CRC(71956ee2) SHA1(a890941e60db358cf45b58909f4719f4826f3bb1) )
	ROM_LOAD( "271b.v3", 0x800000, 0x400000, CRC(ddbbb199) SHA1(0eea4b064bdb8daa03c354fe0a0aa27c4c665bda) )
	ROM_LOAD( "271b.v4", 0xc00000, 0x400000, CRC(01b90c4f) SHA1(387164aa1995d8c11ed939b3afbc294d86d2e27f) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "271b.c1", 0x0000000, 0x800000, CRC(e42fc226) SHA1(1cd9364993e141facdcdd53ec2277df7b275d8a7) )
	ROM_LOAD16_BYTE( "271b.c2", 0x0000001, 0x800000, CRC(1b5e3b58) SHA1(0eb254477a9479541291e43e415310852a0f0bed) )
	ROM_LOAD16_BYTE( "271b.c3", 0x1000000, 0x800000, CRC(d334fdd9) SHA1(1efe30b4f56a55e25ab518cf6999de797b5e407c) )
	ROM_LOAD16_BYTE( "271b.c4", 0x1000001, 0x800000, CRC(0d457699) SHA1(ec73d0c9fc7094d0ac6c0986a6e07cde25893e57) )
	ROM_LOAD16_BYTE( "271b.c5", 0x2000000, 0x800000, CRC(8a91aae4) SHA1(802f4baacf801646be1ef686e105b2e867a6a5df) )
	ROM_LOAD16_BYTE( "271b.c6", 0x2000001, 0x800000, CRC(9f8674b8) SHA1(65964f40b2227d020023fb436579927e65807dcd) )
	ROM_LOAD16_BYTE( "271b.c7", 0x3000000, 0x800000, CRC(374ea523) SHA1(613827d72c6181f3e08353750c9af0c4dbad020b) )
	ROM_LOAD16_BYTE( "271b.c8", 0x3000001, 0x800000, CRC(75211f4d) SHA1(d82f044e816ee539ff131d9c931200c818d34cd0) )
ROM_END



GAME( 2003, kof2003d,   kof2003,  neogeo_noslot, neogeo, neogeo_hbmame, kof2003d,  ROT0, "hack", "Kof2003 (Decrypted P&C)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, kof2003f,   kof2003,  neogeo_noslot, neogeo, neogeo_state,  neogeo,    ROT0, "hack", "Kof2003 Original (Fully Decrypted - Fixed)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, kof2003rebh,kof2003,  no_watchdog,   neogeo, neogeo_state,  neogeo,    ROT0, "hack", "Kof2003 (unknown rebh)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, kof2k3b,    kof2003,  neogeo_noslot, neogeo, neogeo_hbmame, kof2003b,  ROT0, "Gledson01", "Kof2003 (Add Char)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, kof2k3br,   kof2003,  neogeo_noslot, neogeo, neogeo_hbmame, kof2k3br,  ROT0, "Neogeo BR team", "Kof2003 Portuguese Brazilian Hack", MACHINE_SUPPORTS_SAVE )
GAME( 2003, kof2k3bs4,  kof2003,  neogeo_noslot, neogeo, neogeo_state,  neogeo,    ROT0, "EGCG / FCHT", "Kof2003 (Boss, PS2 version, EGCG/FCHT Hack Set 4)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, kof2k3d,    kof2003,  neogeo_noslot, neogeo, neogeo_hbmame, kof2k3d,   ROT0, "hack", "Kof2003 (NGM-2710)(decrypted C)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, kof2k3evo,  kof2003,  no_watchdog,   neogeo, neogeo_state,  neogeo,    ROT0, "hack", "Kof2003 (Evolution 1.4)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, kof2k3gc,   kof2003,  neogeo_noslot, neogeo, neogeo_hbmame, kof2003b,  ROT0, "Gledson01", "Kof2003 (Char color changed for Terry (4P), Athena (3P), Ash (3P), Leona (3P), K' (4P) and King (2P) )", MACHINE_SUPPORTS_SAVE )
GAME( 2003, kof2k3hd,   kof2003,  neogeo_noslot, neogeo, neogeo_hbmame, kof2k3hd,  ROT0, "hack", "Kof2003 (NGH-2710)(decrypted C)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, kof2k3pcd,  kf2k3pcb, neogeo_noslot, neogeo, neogeo_hbmame, kof2k3pcd, ROT0, "hack", "Kof2003 (Japan, JAMMA PCB / decrypted C&Bios)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, kof2k3ps2,  kof2003,  neogeo_noslot, neogeo, neogeo_state,  neogeo,    ROT0, "hack", "Kof2003 (PS2 beta 1.0)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, kof2k3ryu,  kof2003,  no_watchdog,   neogeo, neogeo_state,  neogeo,    ROT0, "Iori Yagami", "Kof2003 (Ryu Hack by Iori Yagami)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, kof2k3sc,   kof2003,  neogeo_noslot, neogeo, neogeo_hbmame, kof2003b,  ROT0, "SHIPDS", "Kof2003 (Color changed)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, kof2k3tc,   kof2003,  neogeo_noslot, neogeo, neogeo_hbmame, kof2003b,  ROT0, "T.Com", "Kof2003 (Char color changed for Kyo (2P/4P), DUOLON (4P), K' (4P) )", MACHINE_SUPPORTS_SAVE )
GAME( 2003, kof2k3zgf,  kof2003,  neogeo_noslot, neogeo, neogeo_hbmame, kof2003b,  ROT0, "Zhaolu94", "Kof2003 (Attack cremation green)", MACHINE_SUPPORTS_SAVE )
