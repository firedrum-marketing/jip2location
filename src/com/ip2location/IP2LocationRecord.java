package com.ip2location;

import java.math.*;

public class IP2LocationRecord {
	IP2LocationRecord() {
	}

	String countryShort;
	String countryLong;
	String region;
	String city;
	String isp;
	BigDecimal latitude;
	BigDecimal longitude;
	String domain;
	String zipCode;
	String timeZone;
	String netSpeed;
	String iddCode;
	String areaCode;
	String weatherStationCode;
	String weatherStationName;
	String mcc;
	String mnc;
	String mobileBrand;
	BigDecimal elevation;
	String usageType;

	public String getCountryShort() {
		return countryShort;
	}

	public String getCountryLong() {
		return countryLong;
	}

	public String getRegion() {
		return region;
	}

	public String getCity() {
		return city;
	}

	public String getIsp() {
		return isp;
	}

	public BigDecimal getLatitude() {
		return latitude;
	}

	public BigDecimal getLongitude() {
		return longitude;
	}

	public String getDomain() {
		return domain;
	}

	public String getZipCode() {
		return zipCode;
	}

	public String getTimeZone() {
		return timeZone;
	}

	public String getNetSpeed() {
		return netSpeed;
	}

	public String getIddCode() {
		return iddCode;
	}

	public String getAreaCode() {
		return areaCode;
	}

	public String getWeatherStationCode() {
		return weatherStationCode;
	}

	public String getWeatherStationName() {
		return weatherStationName;
	}

	public String getMcc() {
		return mcc;
	}

	public String getMnc() {
		return mnc;
	}

	public String getMobileBrand() {
		return mobileBrand;
	}

	public BigDecimal getElevation() {
		return elevation;
	}

	public String getUsageType() {
		return usageType;
	}
}