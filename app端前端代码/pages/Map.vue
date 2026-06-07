<template>
	<view class="container">
		<view class="page-body">
			<view class="page-section page-section-gap">
				<map style="width: 100%; height: 100%;" :latitude="latitude" :longitude="longitude" :markers="covers"
					:polyline="polylines">
				</map>
			</view>
		</view>
	</view>
</template>

<script setup>
	import {
		ref,
		onMounted
	} from 'vue';

	const latitude = ref(39.124257);
	const longitude = ref(117.195256);


	const startLatitude = ref(39.124257);
	const startLongitude = ref(117.195256);
	const endLatitude = ref(39.119257);
	const endLongitude = ref(117.195256);


	const covers = ref([]);
	const polylines = ref([]);


	const generateRandomMarkers = (count, baseLat, baseLng, offset) => {
		const markers = [];
		for (let i = 0; i < count; i++) {
			const randomLat = baseLat + (Math.random() - 0.5) * offset;
			const randomLng = baseLng + (Math.random() - 0.5) * offset;
			markers.push({
				latitude: randomLat,
				longitude: randomLng,
				iconPath: '../../../static/location.png'
			});
		}
		return markers;
	};

	const updateRoute = () => {
		const routePoints = [{
				latitude: startLatitude.value,
				longitude: startLongitude.value
			},
			{
				latitude: 39.1236,
				longitude: 117.1960
			},
			{
				latitude: 39.1233,
				longitude: 117.1970
			},
			{
				latitude: 39.1229,
				longitude: 117.1980
			},
			{
				latitude: endLatitude.value,
				longitude: endLongitude.value
			}
		];

		polylines.value = [{
			points: routePoints,
			color: "#FF0000AA",
			width: 4,
			dottedLine: false
		}];


		covers.value = [{
				latitude: startLatitude.value,
				longitude: startLongitude.value,
				iconPath: '../../../static/location.png'
			},
			{
				latitude: endLatitude.value,
				longitude: endLongitude.value,
				iconPath: '../../../static/location.png'
			}
		];


		const totalMarkers = 10;
		const offset = 0.0005;
		const step = Math.floor(totalMarkers / (routePoints.length - 1));

		for (let i = 0; i < routePoints.length - 1; i++) {
			const startPoint = routePoints[i];
			const endPoint = routePoints[i + 1];

			for (let j = 0; j < step; j++) {
				const lat = startPoint.latitude + (endPoint.latitude - startPoint.latitude) * (j / step);
				const lng = startPoint.longitude + (endPoint.longitude - startPoint.longitude) * (j / step);
				const randomMarkers = generateRandomMarkers(1, lat, lng, offset);
				covers.value.push(...randomMarkers);
			}
		}
	};

	onMounted(() => {
		updateRoute();
	});
</script>

<style>
	.container {
		display: flex;
		flex-direction: column;
	}

	.page-body {
		padding: 10px;
		flex: 1;
	}

	.page-section {
		margin-bottom: 20px;
		height: 100%;
		width: 100%;
	}
</style>