PART_NAME=firmware
REQUIRE_IMAGE_METADATA=1

platform_check_image() {
	return 0
}

platform_pre_upgrade() {
	local board=$(board_name)

	case "$board" in
	BTHOMEHUBV2B|BTHOMEHUBV3A|BTHOMEHUBV5A|P2812HNUF* )
		nand_do_upgrade $1
		;;
	esac

}

platform_do_upgrade() {
	local board=$(board_name)

        case "$board" in
	RS230|RS353)
		default_do_upgrade $1
		do_fixboss
		;;
	esac
}

disable_watchdog() {
	killall watchdog
	( ps | grep -v 'grep' | grep '/dev/watchdog' ) && {
		echo 'Could not disable watchdog'
		return 1
	}
}
append sysupgrade_pre_upgrade disable_watchdog


do_fixboss() {
        mtd fixboss firmware
}
