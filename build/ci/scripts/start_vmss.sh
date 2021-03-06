#!/bin/sh -eu

cd "$(dirname "$0")/.."
. scripts/env.sh
instance_count="${2:-1}"
computer_name_prefix="$(echo "${AZ_VMSS}" | tr -d '.')-i"

az image show \
  --resource-group "${AZ_RESOURCE_GROUP}" \
  --name "${AZ_IMAGE}" \
  --query tags

az vmss create \
  --resource-group "${AZ_RESOURCE_GROUP}" \
  --name "${AZ_VMSS}" \
  --vm-sku "${AZ_VM_SIZE}" \
  --computer-name-prefix "${computer_name_prefix}" \
  --instance-count "${instance_count}" \
  --image "${AZ_IMAGE}" \
  --lb "" \
  --public-ip-per-vm \
  --admin-username pcp \
  ${AZ_PLAN_INFO}
