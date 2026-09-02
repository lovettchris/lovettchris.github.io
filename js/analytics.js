// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

var siteConsent = null;
var telemetryInitialized = false;

function enableTelemetry() {
    if (!telemetryInitialized) {
        telemetryInitialized = true;
        // todo:
    }
}

function disableTelemetry() {
    if (telemetryInitialized) {
        telemetryInitialized = false;
        // todo:
    }
}

function wcp_ready(err, _siteConsent){
    if (err != undefined) {
        return error;
    } else {
        siteConsent = _siteConsent;
        onConsentChanged();
    }
}

function onConsentChanged() {
    var userConsent = siteConsent.getConsentFor(WcpConsent.consentCategories.Analytics);
    if (!siteConsent.isConsentRequired) {
        // site doesn't need to prompt for cookies so go right ahead and use them!
        enableTelemetry();
    }
    else if (userConsent) {
        // user has consented to using cookies for analytics!
        enableTelemetry();
    }
    else {
        disableTelemetry();
    }
}

function manageCookies() {
    siteConsent.manageConsent();
}

$(document).ready(function () {
    WcpConsent.init("en-US", "cookie-banner", wcp_ready, onConsentChanged);
});
