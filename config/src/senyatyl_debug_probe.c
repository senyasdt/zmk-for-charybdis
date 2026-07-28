#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include <zmk/event_manager.h>
#include <zmk/events/split_peripheral_status_changed.h>
#include <zmk/split/bluetooth/peripheral.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

static struct k_work_delayable senyatyl_debug_probe_work;

static void senyatyl_debug_probe_tick(struct k_work *work) {
    LOG_INF("Senyatyl split peripheral debug: connected=%d bonded=%d",
            zmk_split_bt_peripheral_is_connected(), zmk_split_bt_peripheral_is_bonded());
    k_work_schedule(&senyatyl_debug_probe_work, K_SECONDS(2));
}

static int senyatyl_debug_probe_init(void) {
    LOG_INF("Senyatyl split peripheral debug probe booted");
    k_work_init_delayable(&senyatyl_debug_probe_work, senyatyl_debug_probe_tick);
    k_work_schedule(&senyatyl_debug_probe_work, K_SECONDS(2));
    return 0;
}

SYS_INIT(senyatyl_debug_probe_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);

static int senyatyl_debug_probe_listener(const zmk_event_t *eh) {
    const struct zmk_split_peripheral_status_changed *ev =
        as_zmk_split_peripheral_status_changed(eh);

    if (ev) {
        LOG_INF("Senyatyl split peripheral status changed: connected=%d", ev->connected);
    }

    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(senyatyl_debug_probe, senyatyl_debug_probe_listener);
ZMK_SUBSCRIPTION(senyatyl_debug_probe, zmk_split_peripheral_status_changed);
