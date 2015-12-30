// license:BSD-3-Clause
// copyright-holders:Robbbert
#include "../mame/drivers/nemesis.cpp"

#if 0
static INPUT_PORTS_START( spclone )
	PORT_START("IN0")
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_COIN1 )
	PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_COIN2 )
	PORT_BIT( 0x04, IP_ACTIVE_HIGH, IPT_SERVICE1 )
	PORT_BIT( 0x08, IP_ACTIVE_HIGH, IPT_START1 )
	PORT_BIT( 0x10, IP_ACTIVE_HIGH, IPT_START2 )
	PORT_DIPNAME( 0x20, 0x20, DEF_STR( Flip_Screen ) )  PORT_DIPLOCATION("SWT:1")
	PORT_DIPSETTING(    0x20, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x40, 0x40, DEF_STR( Unused ) )       PORT_DIPLOCATION("SWT:2")
	PORT_DIPSETTING(    0x40, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_SERVICE_DIPLOC( 0x80, IP_ACTIVE_LOW, "SWT:3" )

	PORT_START("IN1")
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x04, IP_ACTIVE_HIGH, IPT_JOYSTICK_UP )   PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x08, IP_ACTIVE_HIGH, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x10, IP_ACTIVE_HIGH, IPT_BUTTON1 ) PORT_PLAYER(1)	// power-up
	PORT_BIT( 0x20, IP_ACTIVE_HIGH, IPT_BUTTON2 ) PORT_PLAYER(1)	// shoot
	PORT_BIT( 0x40, IP_ACTIVE_HIGH, IPT_BUTTON3 ) PORT_PLAYER(1)	// missile
	PORT_DIPNAME( 0x80, 0x00, DEF_STR( Cabinet ) ) PORT_DIPLOCATION("SWT:3")
	PORT_DIPSETTING(    0x00, DEF_STR( Upright ) )
	PORT_DIPSETTING(    0x80, DEF_STR( Cocktail ) )

	PORT_START("IN2")
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x04, IP_ACTIVE_HIGH, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x08, IP_ACTIVE_HIGH, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x10, IP_ACTIVE_HIGH, IPT_BUTTON1 ) PORT_PLAYER(2)
	PORT_BIT( 0x20, IP_ACTIVE_HIGH, IPT_BUTTON2 ) PORT_PLAYER(2)
	PORT_BIT( 0x40, IP_ACTIVE_HIGH, IPT_BUTTON3 ) PORT_PLAYER(2)
	PORT_BIT( 0x80, IP_ACTIVE_HIGH, IPT_UNKNOWN )

	PORT_START("DSW0")
	PORT_DIPNAME( 0x0f, 0x0f, DEF_STR( Coin_A ) ) PORT_DIPLOCATION("SW0:1,2,3,4")
	PORT_DIPSETTING(    0x02, DEF_STR( 4C_1C ) )
	PORT_DIPSETTING(    0x05, DEF_STR( 3C_1C ) )
	PORT_DIPSETTING(    0x08, DEF_STR( 2C_1C ) )
	PORT_DIPSETTING(    0x04, DEF_STR( 3C_2C ) )
	PORT_DIPSETTING(    0x01, DEF_STR( 4C_3C ) )
	PORT_DIPSETTING(    0x0f, DEF_STR( 1C_1C ) )
	PORT_DIPSETTING(    0x03, DEF_STR( 3C_4C ) )
	PORT_DIPSETTING(    0x07, DEF_STR( 2C_3C ) )
	PORT_DIPSETTING(    0x0e, DEF_STR( 1C_2C ) )
	PORT_DIPSETTING(    0x06, DEF_STR( 2C_5C ) )
	PORT_DIPSETTING(    0x0d, DEF_STR( 1C_3C ) )
	PORT_DIPSETTING(    0x0c, DEF_STR( 1C_4C ) )
	PORT_DIPSETTING(    0x0b, DEF_STR( 1C_5C ) )
	PORT_DIPSETTING(    0x0a, DEF_STR( 1C_6C ) )
	PORT_DIPSETTING(    0x09, DEF_STR( 1C_7C ) )
	PORT_DIPSETTING(    0x00, DEF_STR( Free_Play ) )
	PORT_DIPNAME( 0x10, 0x10, "Font" )
	PORT_DIPSETTING(    0x10, "Koi no Hotrock" )
	PORT_DIPSETTING(    0x00, "Gradius III" )
	PORT_DIPNAME( 0x20, 0x20, "k007232" )
	PORT_DIPSETTING(    0x20, "old" )
	PORT_DIPSETTING(    0x00, "new" )
	PORT_DIPNAME( 0x40, 0x40, "Pulse" )
	PORT_DIPSETTING(    0x40, "PULSE" )
	PORT_DIPSETTING(    0x00, "RIPPLE" )
	PORT_DIPNAME( 0x80, 0x80, "2P alone play input" )
	PORT_DIPSETTING(    0x80, "1P" )
	PORT_DIPSETTING(    0x00, "2P" )

	PORT_START("DSW1")
	PORT_DIPNAME( 0x03, 0x03, DEF_STR( Lives ) )
	PORT_DIPSETTING(    0x03, "3" )
	PORT_DIPSETTING(    0x02, "4" )
	PORT_DIPSETTING(    0x01, "5" )
	PORT_DIPSETTING(    0x00, "6" )
	PORT_DIPNAME( 0x04, 0x04, "Stage4 expert limit" )
	PORT_DIPSETTING(    0x04, "on" )
	PORT_DIPSETTING(    0x00, "off" )
	PORT_DIPNAME( 0x18, 0x18, DEF_STR( Bonus_Life ) )
	PORT_DIPSETTING(    0x10, "70k and every 200k" )
	PORT_DIPSETTING(    0x18, "100k and every 300k" )
	PORT_DIPSETTING(    0x08, "10k only" )
	PORT_DIPSETTING(    0x00, "NONE" )
	PORT_DIPNAME( 0x60, 0x40, DEF_STR( Difficulty ) )
	PORT_DIPSETTING(    0x60, DEF_STR( Easy ) )
	PORT_DIPSETTING(    0x40, DEF_STR( Medium ) )
	PORT_DIPSETTING(    0x20, DEF_STR( Hard ) )
	PORT_DIPSETTING(    0x00, DEF_STR( Hardest ) )
	PORT_DIPNAME( 0x80, 0x00, DEF_STR( Demo_Sounds ) )
	PORT_DIPSETTING(    0x80, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
INPUT_PORTS_END
#endif

ROM_START( spclone )
	ROM_REGION( 0x80000, "maincpu", 0 )
	ROM_LOAD16_BYTE( "587yq02.18b",  0x00000, 0x10000, CRC(14c19a46) SHA1(1a65a98c390693949247f4e568fe71cff82d59b4) )
	ROM_LOAD16_BYTE( "587yq05.18c",  0x00001, 0x10000, CRC(fdafc246) SHA1(1641411023f85afe82af749b15d067efc5859f4e) )
	ROM_LOAD16_BYTE( "587-c03.17b",  0x40000, 0x20000, CRC(e5caf6e6) SHA1(f5df4fbc43cfa6e2866558c99dd95ba8dc89dc7a) ) /* Mask rom */
	ROM_LOAD16_BYTE( "587-c06.17c",  0x40001, 0x20000, CRC(c2f567ea) SHA1(0c38fea53f3d4a9ae0deada5669deca4be8c9fd3) ) /* Mask rom */

	ROM_REGION( 0x10000, "audiocpu", 0 )    /* 64k for sound */
	ROM_LOAD(      "587nd09.11j",  0x00000, 0x08000, CRC(bf83b182) SHA1(e702eddffea3bad8944bfab03d53c6e277bca866) )

	ROM_REGION( 0x04000, "vlm", 0 )    /* VLM5030 data? */
	ROM_LOAD(      "587-d08.8g",  0x00000, 0x04000, CRC(f9ac6b82) SHA1(3370fc3a7f82e922e19d54afb3bca7b07fa4aa9a) )

	ROM_REGION( 0x20000, "k007232", 0 )    /* 007232 data */
	ROM_LOAD(      "587-c01.10a", 0x00000, 0x20000, CRC(09fe0632) SHA1(4c3b29c623d70bbe8a938a0beb4638912c46fb6a) ) /* Mask rom */
ROM_END

ROM_START( spcloneo )
	ROM_REGION( 0x80000, "maincpu", 0 )    /* 64k for code */
	ROM_LOAD16_BYTE( "587yq02.18b",  0x00000, 0x10000, CRC(6d49878b) SHA1(95ec8c326cb83d8391f7821868187d68ef734120) )
	ROM_LOAD16_BYTE( "587yq05.18c",  0x00001, 0x10000, CRC(08b8fd27) SHA1(fbbb5f9c795de5a776309cdd7a5678fc0061d52a) )
	ROM_LOAD16_BYTE( "17b.bin",      0x40000, 0x20000, CRC(e5caf6e6) SHA1(f5df4fbc43cfa6e2866558c99dd95ba8dc89dc7a) ) /* Mask rom */
	ROM_LOAD16_BYTE( "17c.bin",      0x40001, 0x20000, CRC(c2f567ea) SHA1(0c38fea53f3d4a9ae0deada5669deca4be8c9fd3) ) /* Mask rom */

	ROM_REGION( 0x10000, "audiocpu", 0 )    /* 64k for sound */
	ROM_LOAD(      "587yq09.11j",      0x00000, 0x08000, CRC(9b72fdc7) SHA1(6634e2c8203cc7a9f5b2135a0b717dc18b0fdf23) )

	ROM_REGION( 0x04000, "vlm", 0 )    /* VLM5030 data? */
	ROM_LOAD(      "587-d08.8g",       0x00000, 0x04000, CRC(f9ac6b82) SHA1(3370fc3a7f82e922e19d54afb3bca7b07fa4aa9a) )

	ROM_REGION( 0x20000, "k007232", 0 )    /* 007232 data */
	ROM_LOAD(      "10a.bin",      0x00000, 0x20000, CRC(09fe0632) SHA1(4c3b29c623d70bbe8a938a0beb4638912c46fb6a) ) /* Mask rom */
ROM_END

GAME( 2007, spclone,  salamand, salamand, lifefrcj, driver_device, 0, ROT0, "Konami", "Salamander (version YY 0.7.3) ", MACHINE_NO_COCKTAIL | MACHINE_SUPPORTS_SAVE )
GAME( 2007, spcloneo, salamand, salamand, lifefrcj, driver_device, 0, ROT0, "Konami", "Salamander (version YY 0.7.2.2)", MACHINE_NO_COCKTAIL | MACHINE_SUPPORTS_SAVE )
