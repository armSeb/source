PART_NAME=firmware
REQUIRE_IMAGE_METADATA=1

platform_check_image() {
	return 0
}

platform_do_upgrade() {
	local board=$(board_name)

	case "$board" in
	bt,homehub-v2b|bt,homehub-v3a|bt,homehub-v5a|zyxel,p-2812hnu-f1|zyxel,p-2812hnu-f3)
		nand_do_upgrade $1
		;;
	case "$board" in
        bintec,rs230|bintec,rs353)
                default_do_upgrade $1
                do_fixboss
                ;;
	*)
		default_do_upgrade "$ARGV"
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
