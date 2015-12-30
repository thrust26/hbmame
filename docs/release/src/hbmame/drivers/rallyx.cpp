// license:BSD-3-Clause
// copyright-holders:Robbbert
#include "../mame/drivers/rallyx.cpp"

INPUT_PORTS_START( nrallyv )
	PORT_START("P1")		/* IN0 */
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_COIN3 )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_BUTTON1 )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_4WAY
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_4WAY
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_4WAY
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_4WAY
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_START1 )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_COIN1 )

	PORT_START("P2")		/* IN1 */
	PORT_DIPNAME( 0x01, 0x01, DEF_STR( Cabinet ) )
	PORT_DIPSETTING(	0x01, DEF_STR( Upright ) )
	PORT_DIPSETTING(	0x00, DEF_STR( Cocktail ) )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_COCKTAIL
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_4WAY PORT_COCKTAIL
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_4WAY PORT_COCKTAIL
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_4WAY PORT_COCKTAIL
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_4WAY PORT_COCKTAIL
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_START2 )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_COIN2 )

	PORT_START("DSW")		/* DSW0 */
	PORT_SERVICE( 0x01, IP_ACTIVE_LOW )
	/* TODO: the bonus score depends on the number of lives */
	PORT_DIPNAME( 0x06, 0x02, DEF_STR( Bonus_Life ) )
	PORT_DIPSETTING(	0x02, "A" )
	PORT_DIPSETTING(	0x04, "B" )
	PORT_DIPSETTING(	0x06, "C" )
	PORT_DIPSETTING(	0x00, DEF_STR( None ) )
	PORT_DIPNAME( 0x38, 0x00, DEF_STR( Difficulty ) )
	PORT_DIPSETTING(	0x10, "1 Car, Medium" )
	PORT_DIPSETTING(	0x28, "1 Car, Hard" )
	PORT_DIPSETTING(	0x18, "2 Cars, Medium" )
	PORT_DIPSETTING(	0x30, "2 Cars, Hard" )
	PORT_DIPSETTING(	0x00, "3 Cars, Easy" )
	PORT_DIPSETTING(	0x20, "3 Cars, Medium" )
	PORT_DIPSETTING(	0x38, "3 Cars, Hard" )
	PORT_DIPSETTING(	0x08, "4 Cars, Easy" )
	PORT_DIPNAME( 0xc0, 0xc0, DEF_STR( Coinage ) )
	PORT_DIPSETTING(	0x40, DEF_STR( 2C_1C ) )
	PORT_DIPSETTING(	0xc0, DEF_STR( 1C_1C ) )
	PORT_DIPSETTING(	0x80, DEF_STR( 1C_2C ) )
	PORT_DIPSETTING(	0x00, DEF_STR( Free_Play ) )
INPUT_PORTS_END

ROM_START( rxtron )
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD( "1b",           0x0000, 0x1000, CRC(5882700d) SHA1(b6029e9730f1694894fe8b729ac0ba8d6712dea9) )
	ROM_LOAD( "rxt_1e",       0x1000, 0x1000, CRC(8d5b88e5) SHA1(95a8bde287325f88cfc7ce12ad900647831b861e) )
	ROM_LOAD( "rxt_1h",       0x2000, 0x1000, CRC(1ecfddc0) SHA1(e800a3bb0e2d35dbfba49c7724689d29ab1912fd) )
	ROM_LOAD( "rxt_1k",       0x3000, 0x1000, CRC(2729e00a) SHA1(1f3d17e8342d8a7db57d64fd890b70e64315752a) )
	
	ROM_REGION( 0x1000, "gfx1", 0 )
	ROM_LOAD( "rxt_8e",       0x0000, 0x1000, CRC(91538868) SHA1(4ba04a56a6255895214bca1e0249e365b95f566d) )
	
	ROM_REGION( 0x0100, "gfx2", 0 )
	ROM_LOAD( "im5623.8m",    0x0000, 0x0100, CRC(3c16f62c) SHA1(7a3800be410e306cf85753b9953ffc5575afbcd6) )  /* dots */	

	ROM_REGION( 0x0120, "proms", 0 )
	ROM_LOAD( "m3-7603.11n",  0x0000, 0x0020, CRC(c7865434) SHA1(70c1c9610ba6f1ead77f347e7132958958bccb31) )  /* palette */
	ROM_LOAD( "im5623.8p",    0x0020, 0x0100, CRC(834d4fda) SHA1(617864d3df0917a513e8255ad8d96ae7a04da5a1) )  /* lookup table */

	ROM_REGION( 0x0200, "namco", 0 )	/* sound proms */
	ROM_LOAD( "im5623.3p",    0x0000, 0x0100, CRC(4bad7017) SHA1(3e6da9d798f5e07fa18d6ce7d0b148be98c766d5) )
	ROM_LOAD( "im5623.2m",    0x0100, 0x0100, CRC(77245b66) SHA1(0c4d0bee858b97632411c440bea6948a74759746) )  /* timing - not used */
ROM_END

ROM_START( nrallyv )
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD( "nrallyx.1b",   0x0000, 0x1000, CRC(9404c8d6) SHA1(ee7e45c22a2fbf72d3ac5ac26ab1111a22623fc5) )
	ROM_LOAD( "nrallyx.1e",   0x1000, 0x1000, CRC(ac01bf3f) SHA1(8e1a7cce92ef709d18727db6ee7f89936f4b8df8) )
	ROM_LOAD( "nrallyx.1h",   0x2000, 0x1000, CRC(aeba29b5) SHA1(2a6e4568729b83c430bf70e43c4146ad6a556b1b) )
	ROM_LOAD( "nrallyx.1k",   0x3000, 0x1000, CRC(78f17da7) SHA1(1e035746a10f91e898166a58093d45bdb158ae47) )

	ROM_REGION( 0x1000, "gfx1", 0 )
	ROM_LOAD( "nrallyv.8e",   0x0000, 0x1000, CRC(031acfc5) SHA1(7e0df966b7f2be416e22ec2c36bb86425138c203) )

	ROM_REGION( 0x0100, "gfx2", 0 )
	ROM_LOAD( "im5623.8m",    0x0000, 0x0100, CRC(3c16f62c) SHA1(7a3800be410e306cf85753b9953ffc5575afbcd6) )  /* dots */

	ROM_REGION( 0x0160, "proms", 0 )
	ROM_LOAD( "nrallyx.pr1",  0x0000, 0x0020, CRC(a0a49017) SHA1(494c920a157e9f876d533c1b0146275a366c4989) )  /* palette */
	ROM_LOAD( "nrallyx.pr2",  0x0020, 0x0100, CRC(b2b7ca15) SHA1(e604d58f2f20ebf042f28b01e74eddeacf5baba9) )  /* lookup table */
	ROM_LOAD( "r-2.4n",       0x0120, 0x0020, CRC(8f574815) SHA1(4f84162db9d58b64742c67dc689eb665b9862fb3) )  /* video layout (not used) */
	ROM_LOAD( "r-3.7k",       0x0140, 0x0020, CRC(b8861096) SHA1(26fad384ed7a1a1e0ba719b5578e2dbb09334a25) )  /* video timing (not used) */

	ROM_REGION( 0x0200, "namco", 0 ) /* sound proms */
	ROM_LOAD( "nrallyx.spr",  0x0000, 0x0100, CRC(b75c4e87) SHA1(450f79a5ae09e34f7624d37769815baf93c0028e) )
	ROM_LOAD( "im5623.2m",    0x0100, 0x0100, CRC(77245b66) SHA1(0c4d0bee858b97632411c440bea6948a74759746) )  /* timing - not used */
ROM_END

GAME( 1998, rxtron,  0, rallyx, rallyx,  driver_device, 0, ROT0,  "Jerky and Sil", "Rally-X Tron", 0 )
GAME( 1981, nrallyv, 0, rallyx, nrallyv, driver_device, 0, ROT90, "hack", "New Rally X (Vertical Screen)", 0 )
